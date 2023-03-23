#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

#define GRAVITATIONAL_CONSTANT 6.6743e-11 // costante di gravitazione universale
#define IRON_BALL_MASS 0.1 // massa della pallina di ferro
#define MAGNETIC_FORCE_CONSTANT 0.0001 // costante di forza magnetica
#define TIME_STEP 0.01 // passo temporale dell'algoritmo
#define SIMULATION_TIME 50.0 // tempo totale di simulazione
static mlx_image_t* image;

typedef struct {
    double x;
    double y;
} Vector2D;

typedef struct {
    Vector2D position;
    Vector2D velocity;
} Object2D;

Vector2D calculateForce(Object2D object, Vector2D magnetPosition) {
    Vector2D direction = {
        magnetPosition.x - object.position.x,
        magnetPosition.y - object.position.y
    };
    double distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    double gravitationalForceMagnitude = GRAVITATIONAL_CONSTANT * IRON_BALL_MASS / pow(distance, 2);
    Vector2D gravitationalForce = {
        gravitationalForceMagnitude * direction.x / distance,
        gravitationalForceMagnitude * direction.y / distance
    };
    Vector2D magneticForce = {
        MAGNETIC_FORCE_CONSTANT * direction.x,
        MAGNETIC_FORCE_CONSTANT * direction.y
    };
    return (Vector2D) {
        gravitationalForce.x + magneticForce.x,
        gravitationalForce.y + magneticForce.y
    };
}

void simulate(Object2D* object, Vector2D magnetPosition) {
    Vector2D force = calculateForce(*object, magnetPosition);
    Vector2D acceleration = {
        force.x / IRON_BALL_MASS,
        force.y / IRON_BALL_MASS
    };
    object->velocity.x += acceleration.x * TIME_STEP;
    object->velocity.y += acceleration.y * TIME_STEP;
    object->position.x += object->velocity.x * TIME_STEP;
    object->position.y += object->velocity.y * TIME_STEP;
}

#include <stdio.h>
#include <unistd.h>
int main() {
   // mlx_t* mlx;
    //mlx = mlx_init(600, 600, "MLX42", true);
  //  image = mlx_new_image(mlx, 600, 600);

    Object2D object = {
        .position = {0.0, 0.0},
        .velocity = {0.0, 0.0}
    };
    Vector2D magnetPosition = {30.0, 30.0};

    double currentTime = 0.0;
    while (currentTime < SIMULATION_TIME) {
        simulate(&object, magnetPosition);
        currentTime += TIME_STEP;
        printf("Object position: (%d, %d)\n", (int)object.position.x, (int)object.position.y);
        usleep(500);
        //mlx_put_pixel(image, (int)object.position.x, (int)object.position.y, 0xFFFFFF);
      // mlx_image_to_window(mlx, image, 0, 0);

    }

	//mlx_loop(mlx);

    return 0;
}

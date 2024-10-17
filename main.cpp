#include <raylib.h>
#include <math.h> // For absolute value function

float x = 200;
float y = 200;
float radius = 50;
float dx = 1.5; // X velocity
float dy = -2; // Y velocity
float gravity = 1;
float friction = 0.7;
float ground = 1; // When y velocity is less then ground, set it equal to 0 (stop y movement)
float slowest = 0.05; // When x velocity is less then slowest, set it equal to 0 (stop x movement)

int main() {
     SetTraceLogLevel(LOG_ERROR); // So there is no text in the terminal
     SetTargetFPS(60);
     InitWindow(800, 800, "Ball Animation");

     while(!WindowShouldClose()) { // While the window is open
          BeginDrawing();

          if(x <= radius || x >= GetScreenWidth() - radius) { // Check collision on x-axis
               dx *= -1;
          }

          if(y <= radius || y >= GetScreenHeight() - radius) { // Check collision on y-axis
               y = GetScreenHeight() - radius; // Set the ball to the floor

               if(dy > ground) { // If the ball is not close enough to the ground, reverse the y velocity, but account for friction
                    dy *= -friction;
               } else {
                    dy = 0;
               }

               if (fabs(dx) > 0) { // If the absolite value of x velocity is greater then zero
                    dx -= friction * 0.1 * (dx / fabs(dx)); // Subtract a slower amount of friction to it, and account for if it is negative or positive
                    if (fabs(dx) < slowest) { // If the dx is to slow, stop the ball on the x-axis
                         dx = 0;
                    }
               }
          }

          dy += gravity; // Add gravity to y velocity (not minus because y = 0 is the top)

          x += dx; // Add our x velocity to our x position
          y += dy; // Add our y velocity to our y position

          ClearBackground(WHITE); // Clear the background to prevent the same ball being drawn over and over again
          DrawCircle(x, y, radius, BLACK); // Draw the circle's coordinates, size, and color

          EndDrawing();
     }

     return 0;
}
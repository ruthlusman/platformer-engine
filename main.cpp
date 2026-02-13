#include <raylib.h>

// variables
constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

Rectangle playerRect = {windowWidth/2.0f, windowHeight/2.0f, 50, 50};
Vector2 playerDirection{};
float playerSpeed = 400;

constexpr int gravity = 1200;
float velocity{};
constexpr float maxFallSpeed = 800.0f;
constexpr float playerJump = -600.0f;

Rectangle floorRect = {0, windowHeight-150, windowWidth, 75};

// functions
void playerInput(const float dt) {
    playerDirection.x = static_cast<float>(IsKeyDown(KEY_RIGHT)) - static_cast<float>(IsKeyDown(KEY_LEFT));
    playerRect.x += playerDirection.x * playerSpeed * dt;
}

void playerGravity(const float dt) {
    if (IsKeyPressed(KEY_SPACE)) {velocity = playerJump;}
    velocity += gravity * dt;
    if (velocity >= maxFallSpeed) {velocity = maxFallSpeed;}
    playerRect.y += velocity * dt;
}

int main() {
    InitWindow(windowWidth, windowHeight, "raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        playerInput(dt);
        playerGravity(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(playerRect, BLUE); // player

        DrawRectangleRec(floorRect, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
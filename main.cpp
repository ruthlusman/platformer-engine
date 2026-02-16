#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <iostream>

struct Player {
    Vector2 pos;
    float width;
    float height;
    float speed;
    float jump;
    bool canJump;
    Vector2 velocity;
    [[nodiscard]] Rectangle getRect() const {
        return {pos.x, pos.y , width, height};
    }
    
};

struct Solid {
    Vector2 pos;
    float width;
    float height;
    [[nodiscard]] Rectangle getRect() const {
        return {pos.x, pos.y, width, height};
    }
};


// variables
constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

Player player = {200, windowWidth/2.0f, 50, 50, 600, -600.0f, true, {}};

constexpr int gravity = 1200;
constexpr float maxFallSpeed = 800.0f;
constexpr float playerJump = -600.0f;

Solid floor1 = {0, windowHeight-150, windowWidth, 55};
Solid wall1 = {400, floor1.pos.y-100, 50, 100};
Solid wall2 = {600, floor1.pos.y-150, 50, 150};

Solid objects[3] = {floor1, wall1, wall2};


// functions
void playerMovement(const float dt) {
    // horizontal
    player.velocity.x = (static_cast<float>(IsKeyDown(KEY_RIGHT)) - static_cast<float>(IsKeyDown(KEY_LEFT))) * player.speed;
    player.pos.x += player.velocity.x * dt;

    // vertical
    if (IsKeyPressed(KEY_SPACE) && player.canJump) {player.velocity.y = playerJump; player.canJump = false;}
    player.velocity.y += gravity * dt;
    if (player.velocity.y >= maxFallSpeed) {player.velocity.y = maxFallSpeed;}
    player.pos.y += player.velocity.y * dt;
}

void collisions() {
    for (const Solid &obj : objects) {
        if (CheckCollisionRecs(player.getRect(), obj.getRect())) {
            /* 1 = player
             * 2 = object which we're colliding with */
            const Vector2 center1 = {player.pos.x + player.width/2, player.pos.y + player.height/2};
            const Vector2 center2 = {obj.pos.x + obj.width/2, obj.pos.y + obj.height/2};

            const Vector2 delta = Vector2Subtract(center1, center2); // if delta.x is - then from left otherwise right. same with y
            const Vector2 halfSize1 = {player.width/2, player.height/2};
            const Vector2 halfSize2 = {obj.width/2, obj.height/2};

            const Vector2 minDist = {halfSize1.x + halfSize2.x - fabsf(delta.x),
                                     halfSize1.y + halfSize2.y - fabsf(delta.y)};
            if (minDist.x < minDist.y) {player.pos.x += copysignf(minDist.x, delta.x);}
            else {player.pos.y += copysignf(minDist.y, delta.y); player.velocity.y = 0; player.canJump = true;}
        }
    }
}

// main window and loop
int main() {
    InitWindow(windowWidth, windowHeight, "platformer");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        playerMovement(dt);
        collisions();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(player.getRect(), BLUE); // player
        DrawRectangleRec(floor1.getRect(), WHITE); // floor
        DrawRectangleRec(wall1.getRect(), WHITE); // small wall
        DrawRectangleRec(wall2.getRect(), WHITE); // big wall
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

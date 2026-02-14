#include <raylib.h>

struct Player {
    float x;
    float y;
    float width;
    float height;
    float speed;
    float jump;
    Vector2 velocity;
    [[nodiscard]] Rectangle getRect() const {
        return {x, y , width, height};
    }
};

struct Floor {
    float x;
    float y;
    float width;
    float height;
    [[nodiscard]] Rectangle getRect() const {
        return {x, y, width, height};
    }
};

// variables
constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

Player player = {windowWidth/2.0f, windowWidth/2.0f, 50, 50, 400, -600.0f, {}};

constexpr int gravity = 1200;
constexpr float maxFallSpeed = 800.0f;
constexpr float playerJump = -600.0f;

Floor floor = {0, windowHeight-150, windowWidth, 55};

// functions
void playerInput(const float dt) {
    player.velocity.x = (static_cast<float>(IsKeyDown(KEY_RIGHT)) - static_cast<float>(IsKeyDown(KEY_LEFT))) * player.speed;
    player.x += player.velocity.x * dt;
}

void playerGravity(const float dt) {
    if (IsKeyPressed(KEY_SPACE)) {player.velocity.y = playerJump;}
    player.velocity.y += gravity * dt;
    if (player.velocity.y >= maxFallSpeed) {player.velocity.y = maxFallSpeed;}
    player.y += player.velocity.y * dt;

}

int main() {
    InitWindow(windowWidth, windowHeight, "platformer");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        playerInput(dt);
        playerGravity(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(player.getRect(), BLUE); // player
        DrawRectangleRec(floor.getRect(), WHITE); // floor

        if (CheckCollisionRecs(player.getRect(), floor.getRect())) {
            // floor and ceilings
            if (player.velocity.y > 0) {player.y = floor.y - player.width;}
            else if (player.velocity.y < 0) {player.y = floor.y + floor.height;}
            player.velocity.y = 0;

        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

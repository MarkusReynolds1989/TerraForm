#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "raylib.h"

typedef struct
{
    Vector2 position;
    int is_passable;
    int is_visible;
    Color color;
} Tile;

GArray *MapTiles;

gboolean is_point_in_rec(Vector2 point, Vector2 location, Vector2 size)
{
    return (point.x >= location.x && point.x <= location.x + size.x && point.y >= location.y && point.y <= location.y + size.y);
}

void Init()
{
    SetTargetFPS(60);
    InitWindow(800, 800, "Terraform");
    MapTiles = g_array_new(FALSE, FALSE, sizeof(Tile));

    // Fill the map tiles.
    for (int x = 0; x < 800; x += 50)
    {
        for (int y = 0; y < 800; y += 50)
        {
            Tile tile = (Tile){(Vector2){x, y}, 1, 1, BROWN};
            g_array_append_val(MapTiles, tile);
        }
    }
}

void Update()
{
    for (int i = 0; i < MapTiles->len; i++)
    {
        Tile current_tile = g_array_index(MapTiles, Tile, i);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_point_in_rec(GetMousePosition(), current_tile.position, (Vector2){50, 50}))
        {
            g_array_index(MapTiles, Tile, i).color = GREEN;
        }
    }
}

void Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < MapTiles->len; i++)
    {
        Tile current_tile = g_array_index(MapTiles, Tile, i);
        DrawRectangle(current_tile.position.x, current_tile.position.y, 50, 50, current_tile.color);
        if (is_point_in_rec(GetMousePosition(), current_tile.position, (Vector2){50, 50}))
        {
            DrawRectangleLines(current_tile.position.x, current_tile.position.y, 50, 50, YELLOW);
        }
    }

    EndDrawing();
}

int main(void)
{
    Init();
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    CloseWindow();
}

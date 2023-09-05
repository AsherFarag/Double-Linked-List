/*******************************************************************************************
*
*   raylib [text] example - Input Box
*
*   Example originally created with raylib 1.7, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "DoubleLinkedList.h"
#include <iostream>

#define MAX_INPUT_CHARS     9

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - input box");

    char Word[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    Rectangle textBox = { screenWidth / 2.0f - 100, 180, 225, 50 };

    Rectangle sortButton = { screenWidth / 2.0f - 62.5f, 300, 150, 50 };
    bool onSortButton = false;

    //SetTargetFPS(10);               // Set our game to run at 10 frames-per-second


    DoubleLinkedList<std::string> StringsList;


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Get char pressed (unicode character) on the queue
        int key = GetKeyPressed();

        onSortButton = false;

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
            {
                Word[letterCount] = (char)key;
                Word[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetKeyPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0)
                letterCount = 0;

            Word[letterCount] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            if (letterCount > 0)
                StringsList.PushBack(Word);

            letterCount = 0;
            Word[0] = '\0';
        }

        if (IsKeyPressed(KEY_DELETE)) // test
        {
            auto i = StringsList.Begin();
            i++;
            StringsList.RemoveFrom(&i);
        }

        if (CheckCollisionPointRec(GetMousePosition(), sortButton))
        {
            onSortButton = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                StringsList.Sort();
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        DrawText("Words:", 2.5f, 0, 20, GRAY);

        int i = 0;
        for (auto iterator = StringsList.Begin(); iterator != StringsList.End(); iterator++)
        {
            i++;
            DrawText(iterator.m_Value->m_Data.c_str(), 2.5f, 20 * i, 25, GRAY);
        }

        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
        // sort button
        if (onSortButton)
            DrawRectangle(sortButton.x, sortButton.y, sortButton.width, sortButton.height, GREEN);
        else
            DrawRectangle(sortButton.x, sortButton.y, sortButton.width, sortButton.height, RED);
        DrawText("Sort", screenWidth / 2.0f - 10, 315, 20, WHITE);

        DrawText(Word, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

        DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}
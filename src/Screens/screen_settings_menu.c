/****************************************************************
 *           - The Settings Screen -
 *  Options and configuration for the game.
 *  Created by Squid on 01/26/2026.
 ****************************************************************/

#include "../../include/UI/UIButton/button.h"
#include "screens.h"
#include <stdio.h>

static GameScreen nextScreen;

static UIButton backButton;
static int backButtonX;
static int backButtonY;
static int backButtonWidth;
static int backButtonHeight;
static Rectangle soundToggleBox;
static int soundToggleSize;
static int soundLabelX;
static int soundLabelY;
static bool soundEnabled = true;

// Volume slider variables
static Rectangle volumeSliderBar;
static Rectangle volumeSliderHandle;
static float volumeLevel = 1.0f;
static bool isDraggingSlider = false;
static int volumeSliderWidth;
static int volumeSliderHeight;
static int volumeHandleWidth;
static int volumeLabelX;
static int volumeLabelY;

static int btnTextSize;
static int titleFontSize;

void InitSettingsScreen(void) {
  titleFontSize = 70;
  btnTextSize = 24;
  backButtonWidth = 220;
  backButtonHeight = 52;
  soundToggleSize = 28;

  // Volume slider dimensions
  volumeSliderWidth = 200;
  volumeSliderHeight = 8;
  volumeHandleWidth = 16;

  backButtonX = (GetScreenWidth() - backButtonWidth) / 2;
  backButtonY = (GetScreenHeight() - backButtonHeight) / 2 + 140;

  nextScreen = SCREEN_SETTINGS;

  InitUiButton(&backButton, (float)backButtonX, (float)backButtonY,
               (float)backButtonWidth, (float)backButtonHeight,
               (Color){83, 196, 253, 255},
               (Color){112, 214, 255, 255},
               (Color){56, 162, 219, 255},
               (Color){22, 44, 54, 255});

  const char *soundLabel = "Sound";
  const int soundLabelWidth = MeasureText(soundLabel, btnTextSize);
  const int toggleSpacing = 12;
  const int groupWidth = soundToggleSize + toggleSpacing + soundLabelWidth;
  const int groupX = (GetScreenWidth() - groupWidth) / 2;
  const int groupY = backButtonY - 90;

  soundToggleBox = (Rectangle){(float)groupX, (float)groupY,
                               (float)soundToggleSize, (float)soundToggleSize};
  soundLabelX = groupX + soundToggleSize + toggleSpacing;
  soundLabelY = groupY + (soundToggleSize - btnTextSize) / 2;

  // Initialize volume slider position (below the sound toggle)
  const char *volumeLabel = "Volume";
  const int volumeLabelWidth = MeasureText(volumeLabel, btnTextSize);
  const int sliderSpacing = 12;
  const int volumeGroupWidth =
      volumeLabelWidth + sliderSpacing + volumeSliderWidth;
  const int volumeGroupX = (GetScreenWidth() - volumeGroupWidth) / 2;
  const int volumeGroupY = groupY + soundToggleSize + 20;

  volumeLabelX = volumeGroupX;
  volumeLabelY = volumeGroupY + (volumeSliderHeight - btnTextSize) / 2 + 4;

  volumeSliderBar =
      (Rectangle){(float)(volumeGroupX + volumeLabelWidth + sliderSpacing),
                  (float)(volumeGroupY + 8), (float)volumeSliderWidth,
                  (float)volumeSliderHeight};

  // Position handle based on current volume level
  float handleX = volumeSliderBar.x +
                  (volumeLevel * (volumeSliderBar.width - volumeHandleWidth));
  volumeSliderHandle =
      (Rectangle){handleX, volumeSliderBar.y - 6, (float)volumeHandleWidth,
                  (float)(volumeSliderHeight + 12)};
}

void UpdateSettingsScreen(void) {
  UpdateUiButton(&backButton);

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
      CheckCollisionPointRec(GetMousePosition(), soundToggleBox)) {
    soundEnabled = !soundEnabled;
    SetMasterVolume(soundEnabled ? volumeLevel : 0.0f);
  }

  // Volume slider interaction
  Vector2 mousePos = GetMousePosition();

  // Check if starting to drag the slider handle or clicking on the bar
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Rectangle sliderClickArea = {volumeSliderBar.x, volumeSliderBar.y - 10,
                                 volumeSliderBar.width,
                                 volumeSliderBar.height + 20};
    if (CheckCollisionPointRec(mousePos, volumeSliderHandle) ||
        CheckCollisionPointRec(mousePos, sliderClickArea)) {
      isDraggingSlider = true;
    }
  }

  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    isDraggingSlider = false;
  }

  // Update slider position while dragging
  if (isDraggingSlider) {
    float newX = mousePos.x - (volumeHandleWidth / 2.0f);
    float minX = volumeSliderBar.x;
    float maxX = volumeSliderBar.x + volumeSliderBar.width - volumeHandleWidth;

    if (newX < minX)
      newX = minX;
    if (newX > maxX)
      newX = maxX;

    volumeSliderHandle.x = newX;
    volumeLevel = (newX - volumeSliderBar.x) /
                  (volumeSliderBar.width - volumeHandleWidth);

    if (soundEnabled) {
      SetMasterVolume(volumeLevel);
    }
  }

  if (IsUiButtonClicked(&backButton)) {
    nextScreen = SCREEN_MENU;
  }
}

void DrawSettingsScreen(void) {
  ClearBackground(BLACK);

  const char *title = "Settings";
  const int titleWidth = MeasureText(title, titleFontSize);
  DrawText(title, (GetScreenWidth() - titleWidth) / 2,
           (GetScreenHeight() / 2) - 180, titleFontSize, DARKGRAY);

  DrawRectangleLinesEx(soundToggleBox, 2, DARKGREEN);
  if (soundEnabled) {
    Rectangle innerBox = {soundToggleBox.x + 4, soundToggleBox.y + 4,
                          soundToggleBox.width - 8, soundToggleBox.height - 8};
    DrawRectangleRec(innerBox, GREEN);
  }
  DrawText("Sound", soundLabelX, soundLabelY, btnTextSize, DARKGRAY);

  // Draw volume slider
  DrawText("Volume", volumeLabelX, volumeLabelY, btnTextSize, DARKGRAY);

  // Draw slider bar background
  DrawRectangleRec(volumeSliderBar, GRAY);

  // Draw filled portion of slider bar
  Rectangle filledBar = {volumeSliderBar.x, volumeSliderBar.y,
                         volumeSliderHandle.x - volumeSliderBar.x +
                             (volumeHandleWidth / 2.0f),
                         volumeSliderBar.height};
  DrawRectangleRec(filledBar, soundEnabled ? GREEN : DARKGRAY);

  // Draw slider handle
  DrawRectangleRec(volumeSliderHandle, soundEnabled ? DARKGREEN : DARKGRAY);
  DrawRectangleLinesEx(volumeSliderHandle, 2, soundEnabled ? GREEN : GRAY);

  // Draw volume percentage text
  char volumeText[8];
  int volumePercent = (int)(volumeLevel * 100 + 0.5f);
  snprintf(volumeText, sizeof(volumeText), "%d%%", volumePercent);
  int volumeTextX = (int)(volumeSliderBar.x + volumeSliderBar.width + 12);
  int volumeTextY = volumeLabelY;
  DrawText(volumeText, volumeTextX, volumeTextY, btnTextSize, DARKGRAY);

  DrawUiButton(&backButton, "BACK", btnTextSize);
}

void UnloadSettingsScreen(void) {
  // Nothing to unload yet
}

GameScreen GetSettingsScreen(void) { return nextScreen; }

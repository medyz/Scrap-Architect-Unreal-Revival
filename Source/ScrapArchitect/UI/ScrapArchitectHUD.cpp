#include "UI/ScrapArchitectHUD.h"
#include "Engine/Canvas.h"

void AScrapArchitectHUD::DrawHUD()
{
    Super::DrawHUD();

    if (Canvas)
    {
        const float CenterX = Canvas->ClipX * 0.5f;
        const float CenterY = Canvas->ClipY * 0.5f;
        const float Size = 4.0f;

        // Простой прицел
        DrawRect(FLinearColor::White, CenterX - Size, CenterY, Size * 2.0f, 1.0f);
        DrawRect(FLinearColor::White, CenterX, CenterY - Size, 1.0f, Size * 2.0f);
    }
}


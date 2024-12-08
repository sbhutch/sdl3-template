#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

typedef struct Application {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Application;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        SDL_Log("%s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    Application* app = SDL_calloc(1, sizeof(Application));
    if (!app) {
        SDL_Log("Failed to create application");
        return SDL_APP_FAILURE;
    }
    *appstate = app;

    app->window = SDL_CreateWindow("Application", 960, 540, 0);
    if (!app->window) {
        SDL_Log("%s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    app->renderer = SDL_CreateRenderer(app->window, NULL);
    if (!app->renderer) {
        SDL_Log("%s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_SetRenderVSync(app->renderer, 1)) {
        SDL_Log("%s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    Application* app = appstate;

    if (!SDL_SetRenderDrawColor(app->renderer, 0x64, 0x95, 0xED, 0xFF)) {
        SDL_Log("%s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_RenderClear(app->renderer)) {
        SDL_Log("%s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_RenderPresent(app->renderer)) {
        SDL_Log("%s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    (void)appstate;

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    (void)result;

    Application* app = appstate;

    if (app) {
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_free(app);
    }

    SDL_Quit();
}

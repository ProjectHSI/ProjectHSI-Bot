#include <chrono>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <ProjectHSI-Bot-Shared.h>
#include <ProjectHSI-Bot-Shared-Interface.h>
#include <ProjectHSI-Bot-Shared-Types.h>
#include <SDL.h>
#include <thread>

using namespace std::chrono_literals;

PROJECTHSI_BOT_MODULE_PRESCENE

ABI_CHECK

static void testFunc() {
	SDL_Window *sdlWindow = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, 0);
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);

	bool shouldStop = false;

	while (!shouldStop) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				shouldStop = true;
				break;
			}
		}

		double secondsSinceEpoch = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count() / 1000.0;

		double sine = std::sin(std::fmod(secondsSinceEpoch, 1) * std::numbers::pi);

		SDL_SetRenderDrawColor(sdlRenderer, sine * 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(sdlRenderer);
		SDL_RenderPresent(sdlRenderer);
	}

	SDL_DestroyWindow(sdlWindow);
	SDL_DestroyRenderer(sdlRenderer);
}

const ProjectHSI_Bot_Shared_ModuleInformation moduleInformation {
	"ProjectHSI-Bot-Interface-Default-SDL-GUI",
	ProjectHSI_Bot_Shared_ModuleInformation_Capabilities_Interface
};

const ProjectHSI_Bot_Shared_ModuleInformation init(ProjectHSI_Bot_Shared_Orchestrator_FunctionPointers orchestratorFunctionPointers) {
	printf("Hello, world!\n");

	//testFunc();

	return moduleInformation;
}

void destroy() {
	printf("Goodbye, world!\n");
}
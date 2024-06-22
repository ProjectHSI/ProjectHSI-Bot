/*!
\file ProjectHSI-Bot-Shared-Interface-Types.h

\brief This C header file includes many types expected to be used in Interface modules.
*/

#pragma once

/*!
\brief An as of yet unused enum for ProjectHSI_Bot_Interface_Info. It was intended to contain information about the interface.

\deprecated This enum is not used and may be deleted.
*/
enum ProjectHSI_Bot_Interface_Flags {
	//Graphical = 0b00000001
};

/*!
@brief A struct provided by a GUI-based interface to allow engines to draw objects to a GUI.

This documentation assumes that the interface is GUI-based.

Example implementations of functions will use *SDL2*.

You SHOULD NOT put function pointers to the underlying library/framework function directly.
Instead, you should put an intermediary functions to call the underlying library/framework's respective function.
*/
struct ProjectHSI_Bot_Interface_GraphicalInfo {
	/*!
	\brief A function pointer provided by the interface and used by the engine to draw a background to the GUI.
	
	An implementation of this function could, for instance, could be done with `SDL_RenderClear`, `SDL_DrawRect`, or similiar functions.
	*/
	bool (*drawBackground) (unsigned int colour);

	/*!
	\brief A function pointer provided by the interface and used by the engine to draw a rectangle to the GUI.
	
	An implementation of this function could, for instance, could be done with `SDL_DrawRect`, or similiar functions.
	*/
	bool (*drawRect) (float x, float y, float width, float height, unsigned int colour);
};

/*!
\brief A structed provided by an interface to communicate information about an interface to the orchstrator.
*/
struct ProjectHSI_Bot_Interface_Info {
	/*!
    \brief Unused property for flags.
	
	\deprecated This property is not used, and has no current effect on the interface.
	            It may be removed in a future ABI version.
    */
	unsigned char flags;

	/*!
    \brief This struct is a collection of function pointers provided by a GUI-enabled interface to allow engines to draw to a GUI.
	 
    This pointer SHALL be NULL if the interface doesn't support drawing to a GUI.
    */
	ProjectHSI_Bot_Interface_GraphicalInfo *graphicalInfo;
};
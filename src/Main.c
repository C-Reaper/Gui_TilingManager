#include "/home/codeleaded/System/Static/Library/Scene.h"
#include "/home/codeleaded/System/Static/Library/WindowEngine.h"
#include "/home/codeleaded/System/Static/Library/Random.h"

Scene scene;

void Component1_React(void* parent,TilingManager* b,TilingManagerEvent* be){

}
void Component2_React(void* parent,Button* b,ButtonEvent* be){

}
void Component3_React(void* parent,Button* b,ButtonEvent* be){

}
void Component4_React(void* parent,Button* b,ButtonEvent* be){

}
void Component5_React(void* parent,Editor* b,EditorEvent* be){

}

void Setup(AlxWindow* w){
	// Button ProgressBar Scrollbar Slider Textbox Selection Rotatable
	scene = Scene_New(
		NULL,
		Rect_New(
			(Vec2){ 0.0f,0.0f },
			(Vec2){ 1.0f,1.0f }
		),
		BLACK
	);

	Scene_Add(&scene,(TilingManager[]){
		TilingManager_Make(
			(void*)&scene,
			Component1_React,
			Rect_New((Vec2){ 0.1f,0.1f },(Vec2){ 0.8f,0.8f }),
			GRAY,
			GREEN,
			(void*[]){
				(Button[]){
					Button_NewStd(
						(void*)&scene,
						"Save",
						Component2_React,
						(Vec2){ 32.0f,32.0f },
						Rect_New((Vec2){ 0.0f,0.0f },(Vec2){ 0.25f,0.33f }),
						DARK_CYAN,
						GREEN
					) 
				},
				NULL
			},
			(unsigned int[]){
				sizeof(Button),
				0UL
			}
		) 
	},sizeof(TilingManager));
}

void Update(AlxWindow* w){
	if(w->Strokes[ALX_MOUSE_L].PRESSED && w->Strokes[ALX_KEY_CTRL].DOWN){
		TilingManager* const b = (TilingManager*)scene.childs.First->Memory;
		Button new_button = Button_NewStd(
			&b->renderable,
			"New Button",
			Component2_React,
			(Vec2){ 32.0f,32.0f },
			Rect_New(Vec2_Div(Vec2_Sub(GetMouse(),b->renderable.rect.p),b->renderable.rect.d),(Vec2){ 0.25f,0.25f }),
			DARK_RED,
			GREEN
		);

		TilingManager_Insert(b,&new_button,sizeof(Button));
	}

	Scene_Adapt(&scene,GetWidth(),GetHeight());
	Scene_Update(&scene);

	Scene_Input(&scene,window.Strokes,GetMouse(),GetMouseBefore());

	Clear(BLACK);

	Scene_Render(WINDOW_STD_ARGS,&scene);
}

void Delete(AlxWindow* w){
	Scene_Free(&scene);
}

int main(){
    if(Create("Tiling Manager",2000,1100,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
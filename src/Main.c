#include "/home/codeleaded/System/Static/Library/Scene.h"
#include "/home/codeleaded/System/Static/Library/WindowEngine.h"
#include "/home/codeleaded/System/Static/Library/Random.h"

Scene scene;
Timepoint start;

void Component1_React(void* parent,TilingManager* b,TilingManagerEvent* be){

}
void Component2_React(void* parent,Button* b,ButtonEvent* be){
	if(be->eid == EVENT_PRESSED){
		printf("[%lld] Event: Pressed!\n",(Time_Nano() - start) / TIME_NANO_SECONDS);
	}else if(be->eid == EVENT_DRAGGED){
		printf("[%lld] Event: Dragged!\n",(Time_Nano() - start) / TIME_NANO_SECONDS);
	}
}

void Setup(AlxWindow* w){
	start = Time_Nano();

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
		TilingManager_New(
			(void*)&scene,
			Component1_React,
			Rect_New((Vec2){ 0.1f,0.1f },(Vec2){ 0.8f,0.8f }),
			GRAY,
			GREEN
		) 
	},sizeof(TilingManager));
}

void Update(AlxWindow* w){
	const Vec2 dim = { 100.0f,100.0f };

	if(w->Strokes[ALX_MOUSE_L].PRESSED && w->Strokes[ALX_KEY_CTRL].DOWN){
		TilingManager* const b = (TilingManager*)scene.childs.First->Memory;
		const Pixel colors[] = { WHITE,DARK_RED,ROSE,BLUE,YELLOW,ORANGE };
		
		Button new_button = Button_NewStd(
			&b->renderable,
			"New Button",
			Component2_React,
			(Vec2){ 32.0f,32.0f },
			Rect_New(Vec2_Add(GetMouse(),Vec2_Mulf(dim,0.5f)),dim),
			colors[(uint32_t)(w->MouseX + w->MouseY) % (sizeof(colors) / sizeof(*colors))],
			GREEN
		);

		TilingManager_Insert(b,&new_button,sizeof(Button));
	}else if(w->Strokes[ALX_MOUSE_L].PRESSED && w->Strokes[ALX_KEY_SHIFT].DOWN){
		TilingManager* const b = (TilingManager*)scene.childs.First->Memory;
		const TilingManager_Index id = TilingManager_GetId(b,GetMouse());
		TilingManager_Remove(b,id);
	}

	Scene_Adapt(&scene,GetWidth(),GetHeight());
	Scene_Update(&scene);

	Scene_Input(&scene,window.Strokes,GetMouse(),GetMouseBefore());

	Clear(BLACK);

	Scene_Render(WINDOW_STD_ARGS,&scene);


	const Rect insert = Rect_New(GetMouse(),dim);

	if(!w->Strokes[ALX_MOUSE_L].DOWN && w->Strokes[ALX_KEY_CTRL].DOWN){
		TilingManager* const b = (TilingManager*)scene.childs.First->Memory;
		const Rect rect = TilingManager_SplitRect(b,insert);
		Rect_RenderAlpha(WINDOW_STD_ARGS,rect,0x5544FF44);
	}
	if(!w->Strokes[ALX_MOUSE_L].DOWN && w->Strokes[ALX_KEY_SHIFT].DOWN){
		TilingManager* const b = (TilingManager*)scene.childs.First->Memory;
		const Rect rect = TilingManager_SlotRect(b,insert);
		Rect_RenderAlpha(WINDOW_STD_ARGS,rect,0x55FF4444);
	}
	
	//Rect_RenderAlpha(WINDOW_STD_ARGS,insert,0x770000FF);
}

void Delete(AlxWindow* w){
	Scene_Free(&scene);
}

int main(){
    if(Create("Tiling Manager",2000,1100,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
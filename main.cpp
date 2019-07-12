#include <Urho3D/Core/ProcessUtils.h>

#include <cstdio>
#include <dirent.h>

#include "main.h"
#include "AnimatedCharacter.h"

UrhoViewer::UrhoViewer(Context * context) : Application(context),framecount_(0),time_(0)
{
}

void UrhoViewer::Setup()
{
    AnimatedCharacter::RegisterObject(context_);

    engineParameters_["FullScreen"]=false;
    engineParameters_["WindowWidth"]=1280;
    engineParameters_["WindowHeight"]=720;
    engineParameters_["WindowResizable"]=true;
}

void UrhoViewer::Start()
{
    ResourceCache* cache=GetSubsystem<ResourceCache>();

    GetSubsystem<UI>()->GetRoot()->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
    text_=new Text(context_);
    text_->SetText("Keys: tab = toggle mouse, AWSD = move camera, Shift = fast mode, Esc = quit.\nWait a bit to see FPS.");
    text_->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"),20);
    text_->SetColor(Color(.3,0,.3));
    text_->SetHorizontalAlignment(HA_CENTER);
    text_->SetVerticalAlignment(VA_TOP);
    GetSubsystem<UI>()->GetRoot()->AddChild(text_);

    scene_=new Scene(context_);
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();

    Node *nz = scene_->CreateChild("zone");
    Zone *zone = nz->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.5, 0.5, 0.5));
    zone->SetBoundingBox(BoundingBox(-1000, 1000));

    Node* lightNode = scene_->CreateChild("PointLight");
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_POINT);
    light->SetRange(100.0f);
    light->SetColor(Color(1, 1, 1));
    lightNode->SetPosition(Vector3(2, 2, 2));

    cameraNode_=scene_->CreateChild("Camera");
    Camera* camera=cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(2000);
    cameraNode_->SetPosition(Vector3(0, 1.5, 10));

    Renderer* renderer=GetSubsystem<Renderer>();
    SharedPtr<Viewport> viewport(new Viewport(context_,scene_,cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0,viewport);

    SubscribeToEvent(E_BEGINFRAME,URHO3D_HANDLER(UrhoViewer,HandleBeginFrame));
    SubscribeToEvent(E_KEYDOWN,URHO3D_HANDLER(UrhoViewer,HandleKeyDown));
    SubscribeToEvent(E_UPDATE,URHO3D_HANDLER(UrhoViewer,HandleUpdate));

    // GUI
    auto* uiStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    auto *root = GetSubsystem<UI>()->GetRoot();
    root->SetDefaultStyle(uiStyle);
    anim_holder_ = root->CreateChild<ScrollView>();
    anim_holder_->SetFixedSize(200, 300);
    anim_holder_->SetStyleAuto();

    auto *

    Vector<String> args = GetArguments();

    if (args.Size() > 0)
    {
        LoadModel(args.At(0));
    } else
    {
        printf("\nUsage: u3dv /path/to/model.mdl\n");
        exit(1);
    }
}

void UrhoViewer::Stop()
{
}

void UrhoViewer::HandleBeginFrame(StringHash eventType,VariantMap& eventData)
{
}

void UrhoViewer::HandleKeyDown(StringHash eventType,VariantMap& eventData)
{
    using namespace KeyDown;
    int key=eventData[P_KEY].GetInt();
    if(key==KEY_ESCAPE)
        engine_->Exit();

    if(key==KEY_TAB)
    {
        GetSubsystem<Input>()->SetMouseVisible(!GetSubsystem<Input>()->IsMouseVisible());
    }
}

void UrhoViewer::HandleClosePressed(StringHash eventType,VariantMap& eventData)
{
    engine_->Exit();
}

void UrhoViewer::HandleUpdate(StringHash eventType,VariantMap& eventData)
{
    float timeStep=eventData[Update::P_TIMESTEP].GetFloat();
    framecount_++;
    time_+=timeStep;
    float MOVE_SPEED=10.0f;
    const float MOUSE_SENSITIVITY=0.1f;

    if(time_ >=1)
    {
        std::string str;
        str.append("Keys: tab = toggle mouse, AWSD = move camera, Shift = fast mode, Esc = quit.\n");
        {
            std::ostringstream ss;
            ss<<framecount_;
            std::string s(ss.str());
            str.append(s.substr(0,6));
        }
        str.append(" frames in ");
        {
            std::ostringstream ss;
            ss<<time_;
            std::string s(ss.str());
            str.append(s.substr(0,6));
        }
        str.append(" seconds = ");
        {
            std::ostringstream ss;
            ss<<(float)framecount_/time_;
            std::string s(ss.str());
            str.append(s.substr(0,6));
        }
        str.append(" fps");
        String s(str.c_str(),str.size());
        text_->SetText(s);
          URHO3D_LOGINFO(s);     // this show how to put stuff into the log
        framecount_=0;
        time_=0;
    }

    Input* input=GetSubsystem<Input>();
    if(input->GetKeyDown(KEY_SHIFT))
        MOVE_SPEED*=10;
    if(input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3(0,0, 1)*MOVE_SPEED*timeStep);
    if(input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3(0,0,-1)*MOVE_SPEED*timeStep);
    if(input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3(-1,0,0)*MOVE_SPEED*timeStep);
    if(input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3( 1,0,0)*MOVE_SPEED*timeStep);

    if(!GetSubsystem<Input>()->IsMouseVisible())
    {
        IntVector2 mouseMove=input->GetMouseMove();
        static float yaw_=180;
        static float pitch_=0;
        yaw_+=MOUSE_SENSITIVITY*mouseMove.x_;
        pitch_+=MOUSE_SENSITIVITY*mouseMove.y_;
        pitch_=Clamp(pitch_,-90.0f,90.0f);
        // Reset rotation and set yaw and pitch again
        cameraNode_->SetDirection(Vector3::FORWARD);
        cameraNode_->Yaw(yaw_);
        cameraNode_->Pitch(pitch_);
    }
}

void HandlePostUpdate(StringHash eventType,VariantMap& eventData)
{
}

void UrhoViewer::LoadModel (String filepath)
{
    auto *c_node = scene_->CreateChild("char");
    auto *a_char = c_node->CreateComponent<AnimatedCharacter>();

    printf("loading model %s...\n", filepath.CString());
    a_char->SetModel(filepath);
}

/**
* This macro is expanded to (roughly, depending on OS) this:
*
* > int RunApplication()
* > {
* > Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context());
* > Urho3D::SharedPtr<className> application(new className(context));
* > return application->Run();
* > }
* >
* > int main(int argc, char** argv)
* > {
* > Urho3D::ParseArguments(argc, argv);
* > return function;
* > }
*/

URHO3D_DEFINE_APPLICATION_MAIN(UrhoViewer)


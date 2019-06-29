#include <string>
#include <sstream>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/IO/Log.h>

#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/ScrollView.h>

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Skybox.h>
#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/AnimationState.h>

using namespace Urho3D;

class UrhoViewer : public Application
{
public:
    UrhoViewer (Context *context);
    void Setup ();
    void Start ();
    void Stop ();

    void HandleBeginFrame (StringHash event_type, VariantMap &event_data);
    void HandleKeyDown (StringHash event_type, VariantMap &event_data);
    void HandleClosePressed (StringHash event_type, VariantMap &event_data);
    void HandleUpdate (StringHash event_type, VariantMap &event_data);

private:
    int framecount_;
    float time_;
    SharedPtr<Text> text_;
    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;

    ScrollView *anim_holder_;

    SharedPtr<Node> model_node_;
    SharedPtr<AnimatedModel> model_;

    void LoadModel (String filepath);
};

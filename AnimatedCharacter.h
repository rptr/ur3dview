#pragma once

#include <Urho3D/Scene/LogicComponent.h>

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>

using namespace Urho3D;

namespace Urho3D
{

class AnimatedCharacter : public LogicComponent
{
URHO3D_OBJECT(AnimatedCharacter, LogicComponent);

public:
    explicit AnimatedCharacter (Context *context);
    static void RegisterObject (Context *context);
    void OnNodeSet (Node *node) override;

    void SetModel (String model_file_path);
    void FindAnimationFiles (String filepath);
    void LoadAnimationFile (String filepath);
//    void FixedUpdate (float time_step) override;

protected:
    AnimationController *anim_;
    AnimatedModel *model_;

};

};

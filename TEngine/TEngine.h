#ifndef __TENGINEINCLUDED_H__
#define __TENGINEINCLUDED_H__

// Core
#include "TMemory.h"
#include "TPlatform.h"
#include "TString.h"
#include "TUtil.h"
#include "TSingleton.h"
#include "TDynamicSet.h"
#include "TDynamicArray.h"
#include "TLocator.h"

// Application
#include "TConfig.h"
#include "TApplicationInterface.h"
#include "TTimerInterface.h"

// Game State
#include "TGameStateManager.h"
#include "TGameState.h"

// Events
#include "TEventUpdate.h"
#include "TEventRender.h"
#include "TEventUIUpdate.h"
#include "TEventUIRender.h"
#include "TEventListener.h"

// Entity
#include "TEntity.h"
#include "TEntityDefinition.h"
#include "TPlugin.h"
#include "TPluginDefinition.h"
#include "TPluginRegister.h"

// Scene
#include "TSceneInterface.h"
#include "TRenderableInterface.h"
#include "TSimpleScene.h"

// UI
#include "TFont.h"
#include "TUIVariableParameter.h"
#include "TUIVariableResult.h"
#include "TUIMapping.h"
#include "TUIController.h"
#include "TUIMappingContainer.h"
#include "TUIGroup.h"
#include "TUIButton.h"
#include "TUISlider.h"
#include "TUILabel.h"
#include "TUIHelper.h"
#include "TUIEntity.h"	// TODO: merge UIEntity into entity

// Rendering
#include "TRendererInterface.h"
#include "TSceneInterface.h"
#include "TSpriteDefinition.h"
#include "TSprite.h"
#include "TMesh.h"
#include "TTexture.h"
#include "TMaterial.h"
#include "TColor.h"
#include "TVertex.h"
#include "TCamera.h"
#include "TCameraManager.h"
#include "TShader.h"
#include "TSkin.h"
#include "TPointLight.h"
#include "TSpotLight.h"
#include "TDirectionalLight.h"
#include "TLightManager.h"

// Math
#include "TMath.h"
#include "Collision.h"
#include "TVector3.h"
#include "TVector2.h"
#include "TVector4.h"
#include "TMatrix.h"
#include "TQuaternion.h"
#include "TAABB.h"
#include "TSphere.h"
#include "TTriangle.h"
#include "TPlane.h"
#include "TRay.h"
#include "TLine.h"

// Debug
#include "TDebugRenderer.h"
#include "TError.h"
#include "TDebugInterface.h"

// File System
#include "TDataVariant.h"
#include "TFileSystemInterface.h"
#include "TTextStream.h"
#include "TScreenOutputStream.h"
#include "TXMLStream.h"
#include "TXMLObject.h"
#include "TXMLWriter.h"
#include "TXMLReader.h"

// Audio
#include "TAudioInterface.h"
#include "TSound.h"

// Input
#include "TInputInterface.h"
#include "TCursorManager.h"
#include "TInputMappings.h"

#endif

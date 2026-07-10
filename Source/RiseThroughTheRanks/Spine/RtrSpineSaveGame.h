// Rise Through The Ranks

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RtrSpineTypes.h"
#include "RtrSpineSaveGame.generated.h"

/**
 * Serialized snapshot of the spine (GDD 12.4). Versioned from day one so a
 * multi-year career save survives format changes via migration.
 */
UCLASS()
class RISETHROUGHTHERANKS_API URtrSpineSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	/** Bump on breaking format changes; LoadSpine migrates older versions. */
	static constexpr int32 CurrentVersion = 1;

	UPROPERTY()
	int32 SaveVersion = CurrentVersion;

	UPROPERTY()
	FRtrOfficerRecord Record;

	UPROPERTY()
	FRtrReputationState Reputation;

	UPROPERTY()
	FRtrWorldState WorldState;
};

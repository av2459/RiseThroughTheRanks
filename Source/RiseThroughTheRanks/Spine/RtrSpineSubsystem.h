// Rise Through The Ranks

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RtrSpineTypes.h"
#include "RtrSpineSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRtrOnRecordEntryAdded, const FRtrRecordEntry&, Entry);

/**
 * Owns the spine (GDD 8.8): the single authority for Record, Reputation, and
 * World state. Every system writes outcomes here and reads state from here —
 * this subsystem IS the flywheel's hub.
 *
 * Phase 0 skeleton: minimal write/read API plus save/load, so the greybox
 * Moment Loop prototype has something real to write its Consequence beat to.
 */
UCLASS()
class RISETHROUGHTHERANKS_API URtrSpineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// --- Record ---

	/** Write a Moment Loop outcome to the ledger. The one entry point for the Consequence beat (GDD 4.2). */
	UFUNCTION(BlueprintCallable, Category = "Spine|Record")
	void AddRecordEntry(const FRtrRecordEntry& Entry);

	UFUNCTION(BlueprintPure, Category = "Spine|Record")
	const FRtrOfficerRecord& GetRecord() const { return Record; }

	// --- Reputation ---

	/** Nudge department standing; clamped to [-1, 1]. Driven by consequences, never awarded directly (GDD 8.1). */
	UFUNCTION(BlueprintCallable, Category = "Spine|Reputation")
	void AdjustDepartmentStanding(float Delta);

	/** Nudge a district's community trust; clamped to [-1, 1]. Unknown districts start at 0. */
	UFUNCTION(BlueprintCallable, Category = "Spine|Reputation")
	void AdjustCommunityTrust(FName DistrictId, float Delta);

	UFUNCTION(BlueprintPure, Category = "Spine|Reputation")
	float GetDepartmentStanding() const { return Reputation.DepartmentStanding; }

	UFUNCTION(BlueprintPure, Category = "Spine|Reputation")
	float GetCommunityTrust(FName DistrictId) const;

	// --- World state ---

	UFUNCTION(BlueprintPure, Category = "Spine|World")
	const FRtrWorldState& GetWorldState() const { return WorldState; }

	/** Close out a shift: advances the calendar and shift count (GDD 8.5). */
	UFUNCTION(BlueprintCallable, Category = "Spine|World")
	void CompleteShift();

	// --- Persistence (GDD 12.4: first-class, day one) ---

	UFUNCTION(BlueprintCallable, Category = "Spine|Save")
	bool SaveSpine();

	UFUNCTION(BlueprintCallable, Category = "Spine|Save")
	bool LoadSpine();

	/** Fired whenever the ledger grows — the hook downstream systems (reputation UI, dispatch) listen to. */
	UPROPERTY(BlueprintAssignable, Category = "Spine")
	FRtrOnRecordEntryAdded OnRecordEntryAdded;

private:
	FRtrOfficerRecord Record;
	FRtrReputationState Reputation;
	FRtrWorldState WorldState;
};

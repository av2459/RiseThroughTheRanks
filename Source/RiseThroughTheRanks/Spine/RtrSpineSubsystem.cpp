// Rise Through The Ranks

#include "RtrSpineSubsystem.h"
#include "RtrSpineSaveGame.h"
#include "Kismet/GameplayStatics.h"

namespace
{
	const FString SpineSaveSlot = TEXT("SpineSave");
	constexpr int32 SpineSaveUserIndex = 0;
}

void URtrSpineSubsystem::AddRecordEntry(const FRtrRecordEntry& Entry)
{
	FRtrRecordEntry Stamped = Entry;
	Stamped.Day = WorldState.CurrentDay;
	Record.Entries.Add(Stamped);
	OnRecordEntryAdded.Broadcast(Stamped);
}

void URtrSpineSubsystem::AdjustDepartmentStanding(float Delta)
{
	Reputation.DepartmentStanding = FMath::Clamp(Reputation.DepartmentStanding + Delta, -1.f, 1.f);
}

void URtrSpineSubsystem::AdjustCommunityTrust(FName DistrictId, float Delta)
{
	float& Trust = Reputation.CommunityTrust.FindOrAdd(DistrictId, 0.f);
	Trust = FMath::Clamp(Trust + Delta, -1.f, 1.f);
}

float URtrSpineSubsystem::GetCommunityTrust(FName DistrictId) const
{
	if (const float* Trust = Reputation.CommunityTrust.Find(DistrictId))
	{
		return *Trust;
	}
	return 0.f;
}

void URtrSpineSubsystem::CompleteShift()
{
	WorldState.ShiftsCompleted++;
	WorldState.CurrentDay++;
	SaveSpine();
}

bool URtrSpineSubsystem::SaveSpine()
{
	URtrSpineSaveGame* Save = Cast<URtrSpineSaveGame>(
		UGameplayStatics::CreateSaveGameObject(URtrSpineSaveGame::StaticClass()));
	if (!Save)
	{
		return false;
	}

	Save->Record = Record;
	Save->Reputation = Reputation;
	Save->WorldState = WorldState;

	return UGameplayStatics::SaveGameToSlot(Save, SpineSaveSlot, SpineSaveUserIndex);
}

bool URtrSpineSubsystem::LoadSpine()
{
	URtrSpineSaveGame* Save = Cast<URtrSpineSaveGame>(
		UGameplayStatics::LoadGameFromSlot(SpineSaveSlot, SpineSaveUserIndex));
	if (!Save)
	{
		return false;
	}

	// Version migration lands here when SaveVersion changes (GDD 12.4).

	Record = Save->Record;
	Reputation = Save->Reputation;
	WorldState = Save->WorldState;
	return true;
}

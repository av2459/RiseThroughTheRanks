// Rise Through The Ranks

#pragma once

#include "CoreMinimal.h"
#include "RtrSpineTypes.generated.h"

/**
 * The spine (GDD 8.8): three shared data structures — Record, Reputation,
 * World state — that every system reads from and writes to.
 * Phase 0 skeleton: shapes only, fields grow as systems demand them.
 */

/** What kind of outcome a Moment Loop wrote to the Record (GDD 5.5). */
UENUM(BlueprintType)
enum class ERtrRecordEntryType : uint8
{
	Stop,
	Arrest,
	CaseClosed,
	Commendation,
	Complaint,
	WrongfulStop,
	EvidenceThrownOut,
};

/** One line in the officer's ledger — the atomic output of a Moment Loop's Consequence beat (GDD 4.2). */
USTRUCT(BlueprintType)
struct FRtrRecordEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	ERtrRecordEntryType Type = ERtrRecordEntryType::Stop;

	/** District the entry happened in; drives per-district reputation (GDD 8.1). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	FName DistrictId;

	/** In-world time the entry was written (GDD 8.5 persistent clock). Shape TBD; day count for now. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	int32 Day = 0;

	/** Human-readable summary for the career dashboard (GDD 11.2). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	FText Description;
};

/** The objective log of the job done (GDD 5.5 "Record"). */
USTRUCT(BlueprintType)
struct FRtrOfficerRecord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	TArray<FRtrRecordEntry> Entries;
};

/** Two-audience reputation (GDD 8.1): department standing + per-district community trust. */
USTRUCT(BlueprintType)
struct FRtrReputationState
{
	GENERATED_BODY()

	/** How brass and peers see you. Slow-moving; gates promotion and specialization. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine", meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	float DepartmentStanding = 0.f;

	/** Community trust per district, keyed by DistrictId. -1 (hostile) .. +1 (cooperative). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	TMap<FName, float> CommunityTrust;
};

/** Persistent world state the city remembers between shifts (GDD 8.5, 8.8). */
USTRUCT(BlueprintType)
struct FRtrWorldState
{
	GENERATED_BODY()

	/** Days served on the persistent calendar (GDD 8.5). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	int32 CurrentDay = 0;

	/** Shifts completed — the career clock the grade system reads (GDD 5.3). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	int32 ShiftsCompleted = 0;

	/** Open-ended world flags (e.g. story thread state, district conditions). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spine")
	TMap<FName, bool> WorldFlags;
};

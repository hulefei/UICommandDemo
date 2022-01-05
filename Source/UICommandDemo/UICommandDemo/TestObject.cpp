// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObject.h"

#include "Kismet/GameplayStatics.h"

void UTestObject::Test1(UParticleSystem* ParticleSystem)
{
	UWorld* World = GetWorld();
	check(World)

	UGameplayStatics::SpawnEmitterAtLocation(GetOuter()->GetWorld(), ParticleSystem, FTransform::Identity);
}

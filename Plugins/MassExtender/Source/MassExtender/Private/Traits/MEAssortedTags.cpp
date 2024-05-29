/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "Traits/MEAssortedTags.h"
#include "MassEntityTemplateRegistry.h"
#include "MassEntityTypes.h"

void UMEAssortedTags::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	for (auto& Tag : Tags)
	{
		const UScriptStruct* TagStruct = Tag.GetScriptStruct();

		if (TagStruct->IsChildOf(FMassTag::StaticStruct()))
		{
			BuildContext.AddTag(*TagStruct);
		}
	}
}

#include "SHotPatcher.h"
#include "Styling/SlateTypes.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SCheckBox.h"
#include "EditorStyleSet.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"
#include "IDetailsView.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "AssetRegistryModule.h"
#include "ARFilter.h"
#include "ModuleManager.h"
#include "ISettingsModule.h"
#include "PlatformFile.h"
#include "PlatformFilemanager.h"
#include "FileHelper.h"
#include "json.h"
#include "Misc/SecureHash.h"
#include "FileManager.h"
#include "PackageName.h"
#include "SGridPanel.h"
#include "Cook/SProjectCookPage.h"
#include "VersionControl/SProjectVersionControlPage.h"

#define LOCTEXT_NAMESPACE "FExportPakModule"

void SHotPatcher::Construct(const FArguments& InArgs)
{
	CookModel = MakeShareable(new FHotPatcherCookModel);
	VersionControlModel = MakeShareable(new FHotPatcherVersionControlModel);

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			.Padding(0.0f, 10.0f, 8.0f, 0.0f)
			[
				SNew(SGridPanel)
				.FillColumn(1, 1.0f)

				// cook section
				+ SGridPanel::Slot(0, 0)
				.Padding(8.0f, 0.0f, 0.0f, 0.0f)
				.VAlign(VAlign_Top)
				[
					SNew(STextBlock)
					.Font(FCoreStyle::GetDefaultFontStyle("Cook", 13))
					.Text(LOCTEXT("ProjectCookSectionHeader", "Cook"))
				]
				+ SGridPanel::Slot(1, 0)
				.Padding(32.0f, 0.0f, 8.0f, 0.0f)
				[
					SNew(SProjectCookPage,CookModel)
				]

				+ SGridPanel::Slot(0, 1)
					.ColumnSpan(3)
					.Padding(0.0f, 16.0f)
					[
						SNew(SSeparator)
						.Orientation(Orient_Horizontal)
					]

				// Patch Version Control section
				+ SGridPanel::Slot(0, 2)
					.Padding(8.0f, 0.0f, 0.0f, 0.0f)
					.VAlign(VAlign_Top)
					[
						SNew(STextBlock)
						.Font(FCoreStyle::GetDefaultFontStyle("Patch", 13))
					.Text(LOCTEXT("ProjectPatchSectionHeader", "Patch"))
					]
				+ SGridPanel::Slot(1, 2)
					.Padding(32.0f, 0.0f, 8.0f, 0.0f)
					[
						SNew(SProjectVersionControlPage, VersionControlModel)
					]
			]
		]
	];

}


#undef LOCTEXT_NAMESPACE
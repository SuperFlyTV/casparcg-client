#include "InspectorWidget.h"
#include "Inspector/InspectorBlendModeWidget.h"
#include "Inspector/InspectorBrightnessWidget.h"
#include "Inspector/InspectorContrastWidget.h"
#include "Inspector/InspectorCropWidget.h"
#include "Inspector/InspectorFileRecorderWidget.h"
#include "Inspector/InspectorGeometryWidget.h"
#include "Inspector/InspectorGpiOutputWidget.h"
#include "Inspector/InspectorGridWidget.h"
#include "Inspector/InspectorSaturationWidget.h"
#include "Inspector/InspectorLevelsWidget.h"
#include "Inspector/InspectorVideoWidget.h"
#include "Inspector/InspectorMetadataWidget.h"
#include "Inspector/InspectorOpacityWidget.h"
#include "Inspector/InspectorOutputWidget.h"
#include "Inspector/InspectorTemplateWidget.h"
#include "Inspector/InspectorVolumeWidget.h"
#include "Inspector/InspectorDeckLinkInputWidget.h"
#include "Inspector/InspectorImageScrollerWidget.h"
#include "Inspector/InspectorKeyerWidget.h"
#include "Inspector/InspectorPrintWidget.h"
#include "Inspector/InspectorClearOutputWidget.h"
#include "Inspector/InspectorGroupWidget.h"
#include "Inspector/InspectorSolidColorWidget.h"
#include "Inspector/InspectorAudioWidget.h"
#include "Inspector/InspectorImageWidget.h"
#include "Inspector/InspectorCustomCommandWidget.h"
#include "Inspector/InspectorChromaWidget.h"
#include "Inspector/InspectorOscOutputWidget.h"
#include "Inspector/Atem/InspectorAtemInputWidget.h"
#include "Inspector/Atem/InspectorAtemCutWidget.h"
#include "Inspector/Atem/InspectorAtemAutoWidget.h"
#include "Inspector/Atem/InspectorAtemVideoFormatWidget.h"
#include "Inspector/Atem/InspectorAtemKeyerStateWidget.h"
#include "Inspector/TriCaster/InspectorInputWidget.h"
#include "Inspector/TriCaster/InspectorTakeWidget.h"
#include "Inspector/TriCaster/InspectorAutoWidget.h"
#include "Inspector/TriCaster/InspectorPresetWidget.h"
#include "Inspector/TriCaster/InspectorNetworkSourceWidget.h"
#include "Inspector/TriCaster/InspectorMacroWidget.h"

#include "Global.h"

#include "DeviceManager.h"
#include "EventManager.h"
#include "Commands/AbstractCommand.h"
#include "Commands/BlendModeCommand.h"
#include "Commands/BrightnessCommand.h"
#include "Commands/CommitCommand.h"
#include "Commands/ContrastCommand.h"
#include "Commands/SolidColorCommand.h"
#include "Commands/CropCommand.h"
#include "Commands/GeometryCommand.h"
#include "Commands/GpiOutputCommand.h"
#include "Commands/GridCommand.h"
#include "Commands/GroupCommand.h"
#include "Commands/KeyerCommand.h"
#include "Commands/LevelsCommand.h"
#include "Commands/VideoCommand.h"
#include "Commands/OpacityCommand.h"
#include "Commands/SaturationCommand.h"
#include "Commands/TemplateCommand.h"
#include "Commands/VolumeCommand.h"
#include "Commands/DeckLinkInputCommand.h"
#include "Commands/ImageScrollerCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/CustomCommand.h"
#include "Commands/OscOutputCommand.h"
#include "Commands/Atem/AtemInputCommand.h"
#include "Commands/Atem/AtemCutCommand.h"
#include "Commands/Atem/AtemAutoCommand.h"
#include "Commands/Atem/AtemKeyerStateCommand.h"
#include "Commands/Atem/AtemVideoFormatCommand.h"
#include "Commands/TriCaster/InputCommand.h"
#include "Commands/TriCaster/TakeCommand.h"
#include "Commands/TriCaster/AutoCommand.h"
#include "Commands/TriCaster/PresetCommand.h"
#include "Commands/TriCaster/NetworkSourceCommand.h"
#include "Commands/TriCaster/MacroCommand.h"

InspectorWidget::InspectorWidget(QWidget* parent)
    : QWidget(parent),
      masterVolumeMuted(false), disableCommand(false)
{
    setupUi(this);

    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(0)), 0, new InspectorMetadataWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(1)), 0, new InspectorOutputWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(2)), 0, new InspectorTemplateWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(3)), 0, new InspectorVideoWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(4)), 0, new InspectorBlendModeWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(5)), 0, new InspectorBrightnessWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(6)), 0, new InspectorContrastWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(7)), 0, new InspectorCropWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(8)), 0, new InspectorGeometryWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(9)), 0, new InspectorGridWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(10)), 0, new InspectorLevelsWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(11)), 0, new InspectorOpacityWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(12)), 0, new InspectorSaturationWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(13)), 0, new InspectorVolumeWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(14)), 0, new InspectorDeckLinkInputWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(15)), 0, new InspectorGpiOutputWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(16)), 0, new InspectorImageScrollerWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(17)), 0, new InspectorFileRecorderWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(18)), 0, new InspectorKeyerWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(19)), 0, new InspectorPrintWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(20)), 0, new InspectorClearOutputWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(21)), 0, new InspectorGroupWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(22)), 0, new InspectorSolidColorWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(23)), 0, new InspectorAudioWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(24)), 0, new InspectorImageWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(25)), 0, new InspectorCustomCommandWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(26)), 0, new InspectorChromaWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(27)), 0, new InspectorInputWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(28)), 0, new InspectorTakeWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(29)), 0, new InspectorAutoWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(30)), 0, new InspectorPresetWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(31)), 0, new InspectorNetworkSourceWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(32)), 0, new InspectorMacroWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(33)), 0, new InspectorOscOutputWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(34)), 0, new InspectorAtemInputWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(35)), 0, new InspectorAtemCutWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(36)), 0, new InspectorAtemAutoWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(37)), 0, new InspectorAtemKeyerStateWidget(this));
    this->treeWidgetInspector->setItemWidget(new QTreeWidgetItem(this->treeWidgetInspector->topLevelItem(38)), 0, new InspectorAtemVideoFormatWidget(this));

    this->treeWidgetInspector->expandAll();

    this->treeWidgetInspector->topLevelItem(1)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(2)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(3)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(4)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(5)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(6)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(7)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(8)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(9)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(10)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(11)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(12)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(13)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(14)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(15)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(16)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(17)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(18)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(19)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(20)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(21)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(22)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(23)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(24)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(25)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(26)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(27)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(28)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(29)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(30)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(31)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(32)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(33)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(34)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(35)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(36)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(37)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(38)->setHidden(true);

    QObject::connect(&EventManager::getInstance(), SIGNAL(rundownItemSelected(const RundownItemSelectedEvent&)), this, SLOT(rundownItemSelected(const RundownItemSelectedEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(libraryItemSelected(const LibraryItemSelectedEvent&)), this, SLOT(libraryItemSelected(const LibraryItemSelectedEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(emptyRundown(const EmptyRundownEvent&)), this, SLOT(emptyRundown(const EmptyRundownEvent&)));
}

void InspectorWidget::rundownItemSelected(const RundownItemSelectedEvent& event)
{
    this->treeWidgetInspector->topLevelItem(1)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(2)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(3)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(4)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(5)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(6)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(7)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(8)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(9)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(10)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(11)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(12)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(13)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(14)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(15)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(16)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(17)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(18)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(19)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(20)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(21)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(22)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(23)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(24)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(25)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(26)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(27)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(28)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(29)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(30)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(31)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(32)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(33)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(34)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(35)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(36)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(37)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(38)->setHidden(true);

    if (dynamic_cast<TemplateCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(2)->setHidden(false);
    }
    else if (dynamic_cast<AudioCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(23)->setHidden(false);
    }
    else if (dynamic_cast<ImageCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(24)->setHidden(false);
    }
    else if (dynamic_cast<VideoCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(3)->setHidden(false);
    }
    else if (dynamic_cast<BlendModeCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(4)->setHidden(false);
    }
    else if (dynamic_cast<BrightnessCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(5)->setHidden(false);
    }
    else if (dynamic_cast<ContrastCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(6)->setHidden(false);
    }
    else if (dynamic_cast<CropCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(7)->setHidden(false);
    }
    else if (dynamic_cast<GeometryCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(8)->setHidden(false);
    }
    else if (dynamic_cast<GridCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(9)->setHidden(false);
    }
    else if (dynamic_cast<KeyerCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(18)->setHidden(false);
    }
    else if (dynamic_cast<CommitCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
    }
    else if (dynamic_cast<LevelsCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(10)->setHidden(false);
    }
    else if (dynamic_cast<OpacityCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(11)->setHidden(false);
    }
    else if (dynamic_cast<SaturationCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(12)->setHidden(false);
    }
    else if (dynamic_cast<VolumeCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(13)->setHidden(false);
    }
    else if (dynamic_cast<GpiOutputCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(15)->setHidden(false);
    }
    else if (dynamic_cast<DeckLinkInputCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(14)->setHidden(false);
    }
    else if (dynamic_cast<ImageScrollerCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(16)->setHidden(false);
    }
    else if (dynamic_cast<FileRecorderCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(17)->setHidden(false);
    }
    else if (dynamic_cast<PrintCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(19)->setHidden(false);
    }
    else if (dynamic_cast<ClearOutputCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(20)->setHidden(false);
    }
    else if (dynamic_cast<SolidColorCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(22)->setHidden(false);
    }
    else if (dynamic_cast<GroupCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(21)->setHidden(false);
    }
    else if (dynamic_cast<CustomCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(25)->setHidden(false);
    }
    else if (dynamic_cast<ChromaCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(26)->setHidden(false);
    }
    else if (dynamic_cast<InputCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(27)->setHidden(false);
    }
    else if (dynamic_cast<TakeCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(28)->setHidden(false);
    }
    else if (dynamic_cast<AutoCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(29)->setHidden(false);
    }
    else if (dynamic_cast<PresetCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(30)->setHidden(false);
    }
    else if (dynamic_cast<NetworkSourceCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(31)->setHidden(false);
    }
    else if (dynamic_cast<MacroCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(32)->setHidden(false);
    }
    else if (dynamic_cast<OscOutputCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(33)->setHidden(false);
    }
    else if (dynamic_cast<AtemInputCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(34)->setHidden(false);
    }
    else if (dynamic_cast<AtemCutCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(35)->setHidden(false);
    }
    else if (dynamic_cast<AtemAutoCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(36)->setHidden(false);
    }
    else if (dynamic_cast<AtemKeyerStateCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(37)->setHidden(false);
    }
    else if (dynamic_cast<AtemVideoFormatCommand*>(event.getCommand()))
    {
        this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
        this->treeWidgetInspector->topLevelItem(38)->setHidden(false);
    }
}

void InspectorWidget::emptyRundown(const EmptyRundownEvent& event)
{
    this->treeWidgetInspector->topLevelItem(0)->setHidden(false);
    this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
    this->treeWidgetInspector->topLevelItem(2)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(3)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(4)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(5)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(6)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(7)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(8)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(9)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(10)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(11)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(12)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(13)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(14)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(15)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(16)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(17)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(18)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(19)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(20)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(21)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(22)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(23)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(24)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(25)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(26)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(27)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(28)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(29)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(30)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(31)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(32)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(33)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(34)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(35)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(36)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(37)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(38)->setHidden(true);
}

void InspectorWidget::libraryItemSelected(const LibraryItemSelectedEvent& event)
{
    this->treeWidgetInspector->topLevelItem(0)->setHidden(false);
    this->treeWidgetInspector->topLevelItem(1)->setHidden(false);
    this->treeWidgetInspector->topLevelItem(2)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(3)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(4)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(5)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(6)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(7)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(8)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(9)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(10)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(11)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(12)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(13)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(14)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(15)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(16)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(17)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(18)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(19)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(20)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(21)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(22)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(23)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(24)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(25)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(26)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(27)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(28)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(29)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(30)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(31)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(32)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(33)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(34)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(35)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(36)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(37)->setHidden(true);
    this->treeWidgetInspector->topLevelItem(38)->setHidden(true);
}

void InspectorWidget::toggleExpandItem(QTreeWidgetItem* item, int index)
{
    item->setExpanded(!item->isExpanded());
}

void InspectorWidget::masterVolumeClicked()
{
    this->masterVolumeMuted = !this->masterVolumeMuted;

    foreach (const DeviceModel& model, DeviceManager::getInstance().getDeviceModels())
    {
        const QSharedPointer<CasparDevice> device = DeviceManager::getInstance().getDeviceByName(model.getName());
        if (device->isConnected())
        {
            for (int i = 1; i <= model.getChannels(); i++)
                device->setMasterVolume(i, (this->masterVolumeMuted == true) ? 0 : 1);
        }
    }

    if (this->masterVolumeMuted)
    {
        this->toolButtonMasterVolume->setStyleSheet("border-color: firebrick;");
        this->toolButtonMasterVolume->setIcon(QIcon(":/Graphics/Images/MasterVolumeOff.png"));
    }
    else
    {
        this->toolButtonMasterVolume->setStyleSheet("");
        this->toolButtonMasterVolume->setIcon(QIcon(":/Graphics/Images/MasterVolumeOn.png"));
    }
}

void InspectorWidget::disableCommandClicked()
{
    this->disableCommand = !this->disableCommand;

    foreach (const DeviceModel& model, DeviceManager::getInstance().getDeviceModels())
    {
        const QSharedPointer<CasparDevice> device = DeviceManager::getInstance().getDeviceByName(model.getName());
        if (device != NULL)
            device->setDisableCommands(this->disableCommand);
    }

    if (this->disableCommand)
    {
        this->toolButtonDisableCommand->setStyleSheet("border-color: firebrick;");
        this->toolButtonDisableCommand->setIcon(QIcon(":/Graphics/Images/DisableCommandOff.png"));
    }
    else
    {
        this->toolButtonDisableCommand->setStyleSheet("");
        this->toolButtonDisableCommand->setIcon(QIcon(":/Graphics/Images/DisableCommandOn.png"));
    }
}

#include <QTimer>
#include "TVController.h"

void TVController::update_volume_repr() {
    UI->lcdVolume->display(volume);
    if (muted) UI->leVolume->setText("X");
    else UI->leVolume->clear();
}

void TVController::update_channel_repr() {
    UI->lcdChannel->display(channel);
}

TVController::TVController(Ui_TVController* controller, QWidget* _parent): QMainWindow(_parent) {
    assert(controller != nullptr);
    controller->setupUi(this);
    UI = controller;

    channel = 1;
    volume = 10;
    muted = false;
    channel_selection_mode = false;
    update_volume_repr();
    update_channel_repr();
}

//// slots

void TVController::Mute() {
    muted = !muted;
    update_volume_repr();
}

void TVController::VolumeUp() {
    muted = false;
    volume = std::min(100, volume + 5);
    update_volume_repr();
}

void TVController::VolumeDown() {
    muted = false;
    volume = std::max(0, volume - 5);
    update_volume_repr();
}

void TVController::NextChannel() {
    channel_selection_mode = false;
    ++channel;
    if (channel > 99) channel = 1;
    update_channel_repr();
}

void TVController::PrevChannel() {
    channel_selection_mode = false;
    --channel;
    if (channel < 1) channel = 99;
    update_channel_repr();
}

void TVController::InputChannel() {
    auto source = qobject_cast<QPushButton*>(sender());
    assert(source != nullptr);

    auto input = source->text();
    if (!channel_selection_mode) {
        auto validate_input = [this](){
            auto channelStr = UI->leChannel->text().toStdString();
            UI->leChannel->clear();
            if (!channel_selection_mode) return;

            channel_selection_mode = false;
            channel = std::stoi(channelStr);
            update_channel_repr();
        };

        UI->leChannel->setText(input);
        channel_selection_mode = true;
        QTimer::singleShot(2000, validate_input);
    } else {
        auto current = UI->leChannel->text().toStdString();
        if (current.length() >= 2) {
            UI->leChannel->setText(input);
        } else {
            current.append(input.toStdString());
            UI->leChannel->setText(QString::fromStdString(current));
        }
    }
}
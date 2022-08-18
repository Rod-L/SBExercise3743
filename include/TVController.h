#pragma once

#include <QApplication>
#include "ui_TVController.h"

class TVController: public QMainWindow {
    Q_OBJECT
private:
    int channel;
    int volume;
    bool muted;
    bool channel_selection_mode;
    Ui_TVController* UI;

    void update_volume_repr();
    void update_channel_repr();

public:
    explicit TVController(Ui_TVController* controller, QWidget* _parent = nullptr);

public slots:
    void Mute();
    void VolumeUp();
    void VolumeDown();
    void NextChannel();
    void PrevChannel();
    void InputChannel();
};
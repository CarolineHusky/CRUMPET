/*
 *   Copyright 2018 Dan Leinir Turthra Jensen <admin@leinir.dk>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 3, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public License
 *   along with this program; if not, see <https://www.gnu.org/licenses/>
 */

#ifndef TAILCOMMANDMODEL_H
#define TAILCOMMANDMODEL_H

#include <QAbstractListModel>

#include "CommandInfo.h"

class TailCommandModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString tailVersion READ tailVersion NOTIFY tailVersionChanged)
public:
    explicit TailCommandModel(QObject* parent = nullptr);
    ~TailCommandModel() override;

    enum Roles {
        Name = Qt::UserRole + 1,
        Command,
        IsRunning,
        Category,
        Duration,
        MinimumCooldown,
        CommandIndex
    };

    QHash< int, QByteArray > roleNames() const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * Clear the model of all known commands
     */
    void clear();

    /**
     * Add a new command to the model.
     * The new command is added at the start of the unsorted model
     * The model takes ownership of the command, and deletion should not
     * be done manually.
     * @param command The new command to show in the model
     */
    void addCommand(const CommandInfo& command);
    Q_SIGNAL void commandAdded(const CommandInfo& command);
    /**
     * Remove a command from the model.
     * The entry will be deleted by this function, and you should not attempt to
     * use the instance afterwards.
     * If the command is not maintained by this model, it will still be deleted!
     */
    void removeCommand(const CommandInfo& command);
    Q_SIGNAL void commandRemoved(const CommandInfo& command);

    /**
     * Automatically fill the model with known commands for the specified version
     * of digitail.
     * @param version The version for the tail we've been connected to
     */
    void autofill(const QString& version);
    void setRunning(const QString& command, bool isRunning);

    QString tailVersion() const;
    Q_SIGNAL void tailVersionChanged();

    /**
     * Get all the commands in this model
     *
     * @return A list of all commands currently managed by this model
     */
    const CommandInfoList& allCommands() const;
private:
    class Private;
    Private* d;
};

#endif//TAILCOMMANDMODEL_H

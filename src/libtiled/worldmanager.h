/*
 * worldmanager.h
 * Copyright 2017, Thorbjørn Lindeijer <bjorn@lindeijer.nl>
 *
 * This file is part of libtiled.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "tiled_global.h"

#include <QHash>
#include <QPoint>
#include <QRect>
#include <QRegularExpression>
#include <QSize>
#include <QVector>

namespace Tiled {

struct TILEDSHARED_EXPORT World
{
    struct Pattern
    {
        QRegularExpression regexp;
        int multiplierX;
        int multiplierY;
        QPoint offset;
        QSize mapSize;
    };

    struct MapEntry
    {
        QString fileName;
        QRect rect;
    };

    QString fileName;
    QVector<MapEntry> maps;
    QVector<Pattern> patterns;
    bool onlyShowAdjacentMaps;

    bool containsMap(const QString &fileName) const;
    QRect mapRect(const QString &fileName) const;
    QVector<MapEntry> allMaps() const;
    QVector<MapEntry> mapsInRect(const QRect &rect) const;
    QVector<MapEntry> contextMaps(const QString &fileName) const;
};

class TILEDSHARED_EXPORT WorldManager
{
    Q_DISABLE_COPY(WorldManager)

public:
    static WorldManager &instance();
    static void deleteInstance();

    void loadWorld(const QString &fileName);
    void unloadWorld(const QString &fileName);

    const QHash<QString, World*> &worlds() const { return mWorlds; }

    const World *worldForMap(const QString &fileName) const;

private:
    WorldManager();
    ~WorldManager();

    QHash<QString, World*> mWorlds;

    static WorldManager *mInstance;
};

} // namespace Tiled

#endif // WORLDMANAGER_H

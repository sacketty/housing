/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : Housing.cpp
** Date      : 2012-12-02T21:57:14
** License   : GPL3
** Home Page : https://github.com/pasnox/housing
** Comment   : An application to search for rent / purchase of appartment / house.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This package is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#include "Housing.h"

#include "parser.h"
#include "serializer.h"

#include <QTextDocument>
#include <QDesktopServices>
#include <QFile>
#include <QDir>
#include <QDebug>

QString Housing::toPlainText( const QString& html )
{
    static QTextDocument document;
    document.setHtml( html );
    return document.toPlainText();
}

QVariant Housing::fromJson( const QByteArray& json, bool* ok )
{
    QJson::Parser parser;
    const QVariant variant = parser.parse( json, ok );
    return variant;
}

QByteArray Housing::toJson( const QVariant& variant, bool* ok )
{
    QJson::Serializer serializer;
    const QByteArray json = serializer.serialize( variant, ok );
    return json;
}

QString Housing::settingsFilePath( const QString& extended )
{
    return QDir::toNativeSeparators( QDir::cleanPath(
        QDesktopServices::storageLocation( QDesktopServices::DataLocation )
            .append( "/" )
            .append( extended )
    ) );
}

bool Housing::readJsonFile( QVariant& variant, const QString& name )
{
    const QFileInfo fi( Housing::settingsFilePath( name ) );
    
    if ( fi.exists() ) {
        QFile file( fi.absoluteFilePath() );
        
        if ( !file.open( QIODevice::ReadOnly ) ) {
            qWarning( "%s: Can not open for reading %s", Q_FUNC_INFO, qPrintable( file.fileName() ) );
            return false;
        }
        
        bool ok;
        
        variant = Housing::fromJson( file.readAll(), &ok );
        
        return ok;
    }
    
    return false;
}

bool Housing::writeJsonFile( const QVariant& variant, const QString& name )
{
    const QFileInfo fi( Housing::settingsFilePath( name ) );
    const QString path = fi.absolutePath();
    
    if ( !QFile::exists( path ) ) {
        if ( !QDir().mkpath( path ) ) {
            qWarning( "%s: Can not create path %s", Q_FUNC_INFO, qPrintable( path ) );
            return false;
        }
    }
    
    QFile file( fi.absoluteFilePath() );
    
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) ) {
        qWarning( "%s: Can not open for writing %s", Q_FUNC_INFO, qPrintable( file.fileName() ) );
        return false;
    }
    
    bool ok;
    
    if ( file.write( Housing::toJson( variant, &ok ) ) == -1 ) {
        qWarning( "%s: Can not write in %s", Q_FUNC_INFO, qPrintable( file.fileName() ) );
        return false;
    }
    
    return ok;
}

bool Housing::removeJsonFile( const QString& name )
{
    const QString filePath = Housing::settingsFilePath( name );
    
    if ( QFile::exists( filePath ) ) {
        return QFile::remove( filePath );
    }
    
    return true;
}

QString Housing::googleMapGPSUrl( const double& latitude, const double& longitude, char viewType, int zoom )
{
    /*
        Type:
            h = ground
            m = map
    */
    
    return QString( "https://maps.google.com/?t=%1&z=%2&saddr=%3,%4&daddr=" )
        .arg( viewType )
        .arg( zoom )
        .arg( latitude )
        .arg( longitude )
    ;
}

uint qHash( const QVariant& variant )
{
    switch ( variant.type() ) {
        case QVariant::String:
        case QVariant::Bool:
        case QVariant::Color:
        case QVariant::Date:
        case QVariant::Time:
        case QVariant::DateTime:
        case QVariant::Font:
        case QVariant::KeySequence:
        case QVariant::Locale:
        case QVariant::Url:
            return qHash( variant.toString() );
        case QVariant::ByteArray:
            return qHash( variant.toByteArray() );
        case QVariant::Char:
            return qHash( variant.toChar() );
        case QVariant::StringList:
            return qHash( variant.toStringList().join( QString::null ) );
        case QVariant::Double:
        case QVariant::LongLong:
            return qHash( variant.toLongLong() );
        case QVariant::ULongLong:
            return qHash( variant.toULongLong() );
        case QVariant::Int:
            return qHash( variant.toInt() );
        case QVariant::UInt:
            return qHash( variant.toUInt() );
        default:
            qWarning( "%s: Type not supported: %i, %i, %s", Q_FUNC_INFO, variant.type(), variant.userType(), variant.typeName() );
            break;
    }
    
    return quintptr( &variant );
}

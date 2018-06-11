/***************************************************************************
 *   Copyright (C) 2018 by Chinmoy Ranjan Pradhan <chinmoyrp65@gmail.com>  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "signatureinfo.h"

using namespace Okular;

SignatureInfo::SignatureInfo()
{
}

SignatureInfo::~SignatureInfo()
{
}

SignatureInfo::SignatureStatus SignatureInfo::signatureStatus() const
{
    return SignatureStatusUnknown;
}

SignatureInfo::CertificateStatus SignatureInfo::certificateStatus() const
{
    return CertificateStatusUnknown;
}

QString SignatureInfo::subjectCN() const
{
    return QString();
}

QString SignatureInfo::subjectDN() const
{
    return QString();
}

SignatureInfo::HashAlgorithm SignatureInfo::hashAlgorithm() const
{
    return HashAlgorithmUnknown;
}

QDateTime SignatureInfo::signingTime() const
{
    return QDateTime();
}

QByteArray SignatureInfo::signature() const
{
    return QByteArray();
}

QList<qint64> SignatureInfo::signedRangeBounds() const
{
    return QList<qint64>();
}

bool SignatureInfo::signsTotalDocument() const
{
    return false;
}

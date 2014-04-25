#include "ResourcesManager.h"
#include "ResourcesManager_P.h"

#include <QStandardPaths>

#include "ObfInfo.h"

OsmAnd::ResourcesManager::ResourcesManager(
    const QString& localStoragePath_,
    const QString& userStoragePath_ /*= QString::null*/,
    const QList<QString>& readonlyExternalStoragePaths_ /*= QList<QString>()*/,
    const QString& miniBasemapFilename_ /*= QString::null*/,
    const QString& localTemporaryPath_ /*= QString::null*/,
    const QString& repositoryBaseUrl_ /*= QLatin1String("http://download.osmand.net")*/)
    : _p(new ResourcesManager_P(this))
    , localStoragePath(localStoragePath_)
    , userStoragePath(userStoragePath_)
    , readonlyExternalStoragePaths(readonlyExternalStoragePaths_)
    , miniBasemapFilename(miniBasemapFilename_)
    , localTemporaryPath(!localTemporaryPath_.isNull() ? localTemporaryPath_ : QStandardPaths::writableLocation(QStandardPaths::TempLocation))
    , repositoryBaseUrl(repositoryBaseUrl_)
    , mapStylesCollection(_p->mapStylesCollection)
    , obfsCollection(_p->obfsCollection)
{
    _p->initialize();
    _p->inflateBuiltInResources();
    _p->scanManagedStoragePath();
    _p->rescanUnmanagedStoragePaths();
    _p->loadRepositoryFromCache();
    _p->attachToFileSystem();
}

OsmAnd::ResourcesManager::~ResourcesManager()
{
    _p->detachFromFileSystem();
}

QHash< QString, std::shared_ptr<const OsmAnd::ResourcesManager::BuiltinResource> > OsmAnd::ResourcesManager::getBuiltInResources() const
{
    return _p->getBuiltInResources();
}

std::shared_ptr<const OsmAnd::ResourcesManager::BuiltinResource> OsmAnd::ResourcesManager::getBuiltInResource(const QString& id) const
{
    return _p->getBuiltInResource(id);
}

bool OsmAnd::ResourcesManager::isBuiltInResource(const QString& id) const
{
    return _p->isBuiltInResource(id);
}

bool OsmAnd::ResourcesManager::rescanUnmanagedStoragePaths() const
{
    return _p->rescanUnmanagedStoragePaths();
}

QHash< QString, std::shared_ptr<const OsmAnd::ResourcesManager::LocalResource> > OsmAnd::ResourcesManager::getLocalResources() const
{
    return _p->getLocalResources();
}

std::shared_ptr<const OsmAnd::ResourcesManager::LocalResource> OsmAnd::ResourcesManager::getLocalResource(const QString& id) const
{
    return _p->getLocalResource(id);
}

bool OsmAnd::ResourcesManager::isLocalResource(const QString& id) const
{
    return _p->isLocalResource(id);
}

bool OsmAnd::ResourcesManager::isRepositoryAvailable() const
{
    return _p->isRepositoryAvailable();
}

bool OsmAnd::ResourcesManager::updateRepository() const
{
    return _p->updateRepository();
}

QList< std::shared_ptr<const OsmAnd::ResourcesManager::ResourceInRepository> > OsmAnd::ResourcesManager::getResourcesInRepository() const
{
    return _p->getResourcesInRepository();
}

std::shared_ptr<const OsmAnd::ResourcesManager::ResourceInRepository> OsmAnd::ResourcesManager::getResourceInRepository(const QString& id) const
{
    return _p->getResourceInRepository(id);
}

bool OsmAnd::ResourcesManager::isResourceInRepository(const QString& id) const
{
    return _p->isResourceInRepository(id);
}

bool OsmAnd::ResourcesManager::isResourceInstalled(const QString& id) const
{
    return _p->isResourceInstalled(id);
}

bool OsmAnd::ResourcesManager::uninstallResource(const QString& id)
{
    return _p->uninstallResource(id);
}

bool OsmAnd::ResourcesManager::installFromFile(const QString& filePath, const ResourceType resourceType)
{
    return _p->installFromFile(filePath, resourceType);
}

bool OsmAnd::ResourcesManager::installFromFile(const QString& id, const QString& filePath, const ResourceType resourceType)
{
    return _p->installFromFile(id, filePath, resourceType);
}

bool OsmAnd::ResourcesManager::installFromRepository(const QString& id, const WebClient::RequestProgressCallbackSignature downloadProgressCallback /*= nullptr*/)
{
    return _p->installFromRepository(id, downloadProgressCallback);
}

bool OsmAnd::ResourcesManager::isInstalledResourceOutdated(const QString& id) const
{
    return _p->isInstalledResourceOutdated(id);
}

QList<QString> OsmAnd::ResourcesManager::getOutdatedInstalledResources() const
{
    return _p->getOutdatedInstalledResources();
}

bool OsmAnd::ResourcesManager::updateFromFile(const QString& filePath)
{
    return _p->updateFromFile(filePath);
}

bool OsmAnd::ResourcesManager::updateFromFile(const QString& id, const QString& filePath)
{
    return _p->updateFromFile(id, filePath);
}

bool OsmAnd::ResourcesManager::updateFromRepository(const QString& id, const WebClient::RequestProgressCallbackSignature downloadProgressCallback /*= nullptr*/)
{
    return _p->updateFromRepository(id, downloadProgressCallback);
}

OsmAnd::ResourcesManager::Resource::Metadata::Metadata()
{
}

OsmAnd::ResourcesManager::Resource::Metadata::~Metadata()
{
}

OsmAnd::ResourcesManager::Resource::Resource(
    const QString& id_,
    const ResourceType type_,
    const ResourceOrigin origin_)
    : id(id_)
    , type(type_)
    , origin(origin_)
    , metadata(_metadata)
{
}

OsmAnd::ResourcesManager::Resource::~Resource()
{
}

OsmAnd::ResourcesManager::LocalResource::LocalResource(
    const QString& id_,
    const ResourceType type_,
    const ResourceOrigin origin_,
    const QString& localPath_,
    const uint64_t size_)
    : Resource(id_, type_, origin_)
    , localPath(localPath_)
    , size(size_)
{
    assert(origin_ == ResourceOrigin::Installed || origin_ == ResourceOrigin::Unmanaged);
}

OsmAnd::ResourcesManager::LocalResource::~LocalResource()
{
}

OsmAnd::ResourcesManager::UnmanagedResource::UnmanagedResource(
    const QString& id_,
    const ResourceType type_,
    const QString& localPath_,
    const uint64_t size_,
    const QString& name_)
    : LocalResource(id_, type_, ResourceOrigin::Unmanaged, localPath_, size_)
    , name(name_)
{
}

OsmAnd::ResourcesManager::UnmanagedResource::~UnmanagedResource()
{
}

OsmAnd::ResourcesManager::InstalledResource::InstalledResource(
    const QString& id_,
    const ResourceType type_,
    const QString& localPath_,
    const uint64_t size_,
    const uint64_t timestamp_)
    : LocalResource(id_, type_, ResourceOrigin::Installed, localPath_, size_)
    , timestamp(timestamp_)
{
}

OsmAnd::ResourcesManager::InstalledResource::~InstalledResource()
{
}

OsmAnd::ResourcesManager::BuiltinResource::BuiltinResource(
    const QString& id_,
    const ResourceType type_)
    : Resource(id_, type_, ResourceOrigin::Builtin)
{
}

OsmAnd::ResourcesManager::BuiltinResource::~BuiltinResource()
{
}

OsmAnd::ResourcesManager::BuiltinMapStyleResource::BuiltinMapStyleResource(
    const QString& id_,
    const std::shared_ptr<const MapStyle>& style_)
    : BuiltinResource(id_, ResourceType::MapStyle)
    , style(style_)
{
}

OsmAnd::ResourcesManager::BuiltinMapStyleResource::~BuiltinMapStyleResource()
{
}

OsmAnd::ResourcesManager::BuiltinMapStylesPresetsResource::BuiltinMapStylesPresetsResource(
    const QString& id_,
    const std::shared_ptr<const MapStylesPresets>& presets_)
    : BuiltinResource(id_, ResourceType::OnlineTileSources)
    , presets(presets_)
{
}

OsmAnd::ResourcesManager::BuiltinMapStylesPresetsResource::~BuiltinMapStylesPresetsResource()
{
}

OsmAnd::ResourcesManager::BuiltinOnlineTileSourcesResource::BuiltinOnlineTileSourcesResource(
    const QString& id_,
    const std::shared_ptr<const OnlineTileSources>& sources_)
    : BuiltinResource(id_, ResourceType::OnlineTileSources)
    , sources(sources_)
{
}

OsmAnd::ResourcesManager::BuiltinOnlineTileSourcesResource::~BuiltinOnlineTileSourcesResource()
{
}

OsmAnd::ResourcesManager::ResourceInRepository::ResourceInRepository(
    const QString& id_,
    const ResourceType type_,
    const QUrl& url_,
    const uint64_t size_,
    const uint64_t timestamp_,
    const uint64_t packageSize_)
    : Resource(id_, type_, ResourceOrigin::Repository)
    , url(url_)
    , size(size_)
    , timestamp(timestamp_)
    , packageSize(packageSize_)
{
}

OsmAnd::ResourcesManager::ResourceInRepository::~ResourceInRepository()
{
}

OsmAnd::ResourcesManager::ObfMetadata::ObfMetadata(const std::shared_ptr<const ObfFile>& obfFile_)
    : obfFile(obfFile_)
{
}

OsmAnd::ResourcesManager::ObfMetadata::~ObfMetadata()
{
}

OsmAnd::ResourcesManager::MapStyleMetadata::MapStyleMetadata(const std::shared_ptr<MapStyle>& mapStyle_)
    : mapStyle(mapStyle_)
{
}

OsmAnd::ResourcesManager::MapStyleMetadata::~MapStyleMetadata()
{
}

#ifndef _OSMAND_CORE_MAP_RENDERER_TILED_SYMBOLS_RESOURCE_H_
#define _OSMAND_CORE_MAP_RENDERER_TILED_SYMBOLS_RESOURCE_H_

#include "stdlib_common.h"

#include "QtExtensions.h"

#include "OsmAndCore.h"
#include "MapRendererResourceType.h"
#include "MapRendererResourceState.h"
#include "MapRendererBaseTiledResource.h"
#include "GPUAPI.h"

namespace OsmAnd
{
    class MapRendererResourcesManager;
    class MapRendererTiledSymbolsResourcesCollection;
    class MapSymbol;
    class MapSymbolsGroup;
    class MapTiledSymbols;

    class MapRendererTiledSymbolsResource : public MapRendererBaseTiledResource
    {
    private:
    protected:
        MapRendererTiledSymbolsResource(MapRendererResourcesManager* owner, const TiledEntriesCollection<MapRendererBaseTiledResource>& collection, const TileId tileId, const ZoomLevel zoom);

        class GroupResources
        {
            Q_DISABLE_COPY(GroupResources);
        private:
        protected:
        public:
            GroupResources(const std::shared_ptr<const MapSymbolsGroup>& group);
            ~GroupResources();

            const std::shared_ptr<const MapSymbolsGroup> group;
            QHash< std::shared_ptr<const MapSymbol>, std::shared_ptr<const GPUAPI::ResourceInGPU> > resourcesInGPU;
        };

        std::shared_ptr<const MapTiledSymbols> _sourceData;
        QList< std::shared_ptr<GroupResources> > _uniqueGroupsResources;
        QList< std::shared_ptr<GroupResources> > _referencedSharedGroupsResources;

        virtual bool obtainData(bool& dataAvailable, const IQueryController* queryController);
        virtual bool uploadToGPU();
        virtual void unloadFromGPU();

        virtual bool checkIsSafeToUnlink();
        virtual void detach();
    public:
        virtual ~MapRendererTiledSymbolsResource();

    friend class OsmAnd::MapRendererResourcesManager;
    friend class OsmAnd::MapRendererTiledSymbolsResourcesCollection;
    };
}

#endif // !defined(_OSMAND_CORE_MAP_RENDERER_TILED_SYMBOLS_RESOURCE_H_)

#ifndef _OSMAND_CORE_MAP_RASTERIZER_H_
#define _OSMAND_CORE_MAP_RASTERIZER_H_

#include <OsmAndCore/stdlib_common.h>
#include <functional>

#include <OsmAndCore/QtExtensions.h>
#include <QList>

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>
#include <OsmAndCore/PrivateImplementation.h>
#include <OsmAndCore/Map/MapTypes.h>
#include <OsmAndCore/Map/Primitiviser.h>
#include <OsmAndCore/Map/MapRasterizer_Metrics.h>

class SkCanvas;

namespace OsmAnd
{
    class MapPresentationEnvironment;

    class MapRasterizer_P;
    class OSMAND_CORE_API MapRasterizer
    {
        Q_DISABLE_COPY_AND_MOVE(MapRasterizer);
    private:
        PrivateImplementation<MapRasterizer_P> _p;
    protected:
    public:
        MapRasterizer(const std::shared_ptr<const MapPresentationEnvironment>& mapPresentationEnvironment);
        virtual ~MapRasterizer();

        const std::shared_ptr<const MapPresentationEnvironment> mapPresentationEnvironment;

        void rasterize(
            const std::shared_ptr<const Primitiviser::PrimitivisedArea>& primitivizedArea,
            SkCanvas& canvas,
            const bool fillBackground = true,
            const AreaI* const destinationArea = nullptr,
            MapRasterizer_Metrics::Metric_rasterize* const metric = nullptr,
            const IQueryController* const controller = nullptr);
    };
}

#endif // !defined(_OSMAND_CORE_MAP_RASTERIZER_H_)

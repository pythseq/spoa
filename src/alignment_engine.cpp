/*!
 * @file alignment_engine.cpp
 *
 * @brief AlignmentEngine class source file
 */

#include <limits>
#include <algorithm>

#include "sisd_alignment_engine.hpp"
#include "simd_alignment_engine.hpp"
#include "spoa/alignment_engine.hpp"

namespace spoa {

std::unique_ptr<AlignmentEngine> createAlignmentEngine(
    AlignmentType alignment_type, int8_t match, int8_t mismatch,
    int8_t gap) {

    if (alignment_type != AlignmentType::kSW &&
        alignment_type != AlignmentType::kNW &&
        alignment_type != AlignmentType::kOV) {

        fprintf(stderr, "spoa::createAlignmentEngine error: "
            "invalid alignment type\n");
        exit(1);
    }

    auto alignment_engine = createSimdAlignmentEngine(alignment_type, match,
        mismatch, gap);

    if (alignment_engine == nullptr) {
        return createSisdAlignmentEngine(alignment_type, match, mismatch, gap);
    }

    return alignment_engine;
}

AlignmentEngine::AlignmentEngine(AlignmentType alignment_type, int8_t match,
    int8_t mismatch, int8_t gap)
        : alignment_type_(alignment_type), match_(match), mismatch_(mismatch),
        gap_(gap) {
}

}

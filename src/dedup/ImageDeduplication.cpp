#include <filesystem>
#include "dedup/ImageDeduplication.h"
#include "utils/ImgIo.h"
#include "utils/ImgProc.h"

ImageDeduplication::ImageDeduplication(DeduplicationModel *model) : model(model) {
}

Dedup::Findings ImageDeduplication::findDuplicates(const std::string &path) {
    Dedup::Findings findings;
    std::vector<cv::Mat> encodings;

    for (std::filesystem::recursive_directory_iterator i(path), end; i != end; ++i) {
        if (i->is_regular_file()) {
            std::string imagePath = i->path().string();
            findings.images.emplace_back(imagePath);
            encodings.emplace_back(model->encode(ImgIo::read(imagePath)));
        }
    }

    size_t total = encodings.size();
    findings.duplications.resize(total);

    for (size_t i = 0; i < total; ++i) {
        for (size_t j = i + 1; j < total; ++j) {
            double score = ImgProc::cosineSimilarity(encodings[i], encodings[j]);
            if (score >= modelScoreThreshold) {
                findings.duplications[i].emplace_back(j, (float) score);
                findings.duplications[j].emplace_back(i, (float) score);
            }
        }
    }

    return findings;
}

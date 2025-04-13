add_library(${ProjectName} OBJECT)
target_import_src(${ProjectName})

target_import_boost(${ProjectName} PUBLIC)
target_import_nlohmann_json(${ProjectName} PUBLIC)
target_import_base(${ProjectName} PUBLIC)

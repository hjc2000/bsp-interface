#pragma once

/// @brief 使能缓存。
void DI_EnableCache();

/// @brief 失能缓存。
void DI_DisableCache();

/// @brief 是 D-Cache 无效。
/// @note 即将 D-Cache 的数据标记为过期的，重新从内存中读取数据放到 D-Cache 中。
void DI_InvalidateDCache();

/// @brief 清除 D-Cache。
/// @note 即将原本从内存中读取到 D-Cache 中，并且已经修改过的 D-Cache 的数据写入
/// 内存中而不是仅仅停留在 D-Cache 中。
void DI_CleanDCache();

/// @brief 清除并且无效化 D-Cache.
void DI_CleanAndInvalidateDCache();

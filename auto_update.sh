#!/bin/bash

# Kiểm tra trạng thái Git
if [[ $(git status --porcelain) ]]; then
    git add .                          # Thêm tất cả thay đổi
    git commit -m "Auto-update commit" # Commit với thông điệp tự động
    git push origin game2d             # Đẩy thay đổi lên nhánh game2d
else
    echo "Không có thay đổi nào để cập nhật."
fi


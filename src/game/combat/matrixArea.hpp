// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_MATRIXAREA_H_6F689CB8AE494857B6388358F0C33F36
#define FS_MATRIXAREA_H_6F689CB8AE494857B6388358F0C33F36

#include <cstdint>

class MatrixArea
{
	public:
		MatrixArea(uint32_t rows, uint32_t cols): centerX(0), centerY(0), rows(rows), cols(cols) {
			data_ = new bool*[rows];

			for (uint32_t row = 0; row < rows; ++row) {
				data_[row] = new bool[cols];

				for (uint32_t col = 0; col < cols; ++col) {
					data_[row][col] = 0;
				}
			}
		}

		MatrixArea(const MatrixArea& rhs) {
			centerX = rhs.centerX;
			centerY = rhs.centerY;
			rows = rhs.rows;
			cols = rhs.cols;

			data_ = new bool*[rows];

			for (uint32_t row = 0; row < rows; ++row) {
				data_[row] = new bool[cols];

				for (uint32_t col = 0; col < cols; ++col) {
					data_[row][col] = rhs.data_[row][col];
				}
			}
		}

		~MatrixArea() {
			for (uint32_t row = 0; row < rows; ++row) {
				delete[] data_[row];
			}

			delete[] data_;
		}

		// non-assignable
		MatrixArea& operator=(const MatrixArea&) = delete;

		void setValue(uint32_t row, uint32_t col, bool value) const {
			data_[row][col] = value;
		}
		bool getValue(uint32_t row, uint32_t col) const {
			return data_[row][col];
		}

		void setCenter(uint32_t y, uint32_t x) {
			centerX = x;
			centerY = y;
		}
		void getCenter(uint32_t& y, uint32_t& x) const {
			x = centerX;
			y = centerY;
		}

		uint32_t getRows() const {
			return rows;
		}
		uint32_t getCols() const {
			return cols;
		}

		inline const bool* operator[](uint32_t i) const {
			return data_[i];
		}
		inline bool* operator[](uint32_t i) {
			return data_[i];
		}

	protected:
		uint32_t centerX;
		uint32_t centerY;

		uint32_t rows;
		uint32_t cols;
		bool** data_;
};

#endif

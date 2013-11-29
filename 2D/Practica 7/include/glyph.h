#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

class Glyph
{
	public:
		void SetBeginX(uint16 beginX) { this->beginX = beginX; }
		uint16 GetBeginX() { return this->beginX; }

		void SetBeginY(uint16 beginY) { this->beginY = beginY; }
		uint16 GetBeginY() { return this->beginY; }

		void SetEndX(uint16 endX) { this->endX = endX; }
		uint16 GetEndX() { return this->endX; }

		void SetEndY(uint16 endY) { this->endY = endY; }
		uint16 GetEndY() { return this->endY; }

	private:
		uint16 beginX;
		uint16 beginY;
		uint16 endX;
		uint16 endY;
};

#endif
#include "Image.h"
#include <math.h>
#include <string>
#include <time.h>
RGBA multi(float val, RGBA r) {
	return RGBA(r.r * val, r.g * val, r.b * val);
}
void NearestNeigbor(std::string inputImgPath, int widthFinal, int heightFinal) {
	ColorImage outImg(widthFinal, heightFinal), inputImg;
	inputImg.Load(inputImgPath);
	float scalefactorW = (float)inputImg.GetWidth() / widthFinal;
	float scalefactorH = (float)inputImg.GetHeight() / heightFinal;
	for (int y = 0; y < widthFinal; y++)
	{
		for (int x = 0; x < heightFinal; x++)
		{
			outImg(x, y) = inputImg(x * scalefactorW, y * scalefactorH);
		}
	}
	outImg.Save("Images/3-NN-" + std::to_string(widthFinal) + "x" + std::to_string(heightFinal) + ".png");
	std::cout << "The NearestNeigbor Interpolation successfully." << std::endl;
}
void BilinearInterpolation(std::string inputImgPath, int widthFinal, int heightFinal) {
	ColorImage outImg(widthFinal, heightFinal), inputImg;
	inputImg.Load(inputImgPath);
	int inputImageWidth = inputImg.GetWidth();
	int inputImageHeight = inputImg.GetHeight();
	float scalefactorW = (float)inputImg.GetWidth() / widthFinal;
	float scalefactorH = (float)inputImg.GetHeight() / heightFinal;
	for (int y = 0; y < widthFinal - 1; y++)
	{
		for (int x = 0; x < heightFinal - 1; x++)
		{
			int pxa = (int)(x * scalefactorW);
			int pya = (int)(y * scalefactorH);
			if (pxa >= inputImageWidth - 1 || pya >= inputImageHeight - 1) break;
			float afx1 = (float)x * (float)scalefactorW - (float)pxa;
			float afx2 = 1 - afx1;
			float afy1 = (float)y * (float)scalefactorH - (float)pya;
			float afy2 = 1 - afy1;
			float aw1 = afx2 * afy2;
			float aw2 = afx1 * afy2;
			float aw3 = afx2 * afy1;
			float aw4 = afx1 * afy1;
			RGBA p1 = inputImg(pya, pxa);
			RGBA p2 = inputImg(pya, pxa + 1);
			RGBA p3 = inputImg(pya + 1, pxa);
			RGBA p4 = inputImg(pya + 1, pxa + 1);
			Byte outPixelR = multi(aw1, p1).r + multi(aw2, p2).r + multi(aw3, p3).r + multi(aw4, p4).r;
			Byte outPixelG = multi(aw1, p1).g + multi(aw2, p2).g + multi(aw3, p3).g + multi(aw4, p4).g;
			Byte outPixelB = multi(aw1, p1).b + multi(aw2, p2).b + multi(aw3, p3).b + multi(aw4, p4).b;
			outImg(y, x) = RGBA(outPixelR, outPixelG, outPixelB);
		}
	}
	outImg.Save("Images/3-BL-" + std::to_string(widthFinal) + "x" + std::to_string(heightFinal) + ".png");
	std::cout << "\n\nThe Bilinear Interpolation successfully." << std::endl;
}
int main() {
	std::string inputImgPath = "Images/read2.png";
	clock_t begin = clock();
	NearestNeigbor(inputImgPath, 750, 750);
	clock_t end = clock();
	std::cout << "NearestNeigbor function toke: " << end - begin << std::endl;
	begin = clock();
	BilinearInterpolation(inputImgPath, 750, 750);
	end = clock();
	std::cout << "BilinearInterpolation function toke:" << end - begin << std::endl << std::endl << std::endl;
	return 0;
}

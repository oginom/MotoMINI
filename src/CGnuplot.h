/*
 * http://tips.hecomi.com/entry/20100707/1278533304
 * (アニメーション参考) http://kengo700.hatenablog.com/entry/2016/01/16/gnuplot_%E3%81%A7%E5%AE%9F%E9%A8%93%E3%83%87%E3%83%BC%E3%82%BF%E3%81%AE%E3%82%A2%E3%83%8B%E3%83%A1%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3%E3%82%92%E4%BD%9C%E3%82%8B
 */

#pragma once

/*! @file
 @brief		gnuplotクラス
 @author		hecomi
 @date		July 5, 2010.
*/

#include <vector>
#include <fstream>
#include <string>

class CGnuplot {
private:
	/*! @brief パイプを繋げるファイルポインタ */
	FILE* Fp;

	/*! @brief バッファフラッシュ */
	void Flush();

public:
	/*! @brief コンストラクタ */
	CGnuplot();
	CGnuplot(const char* file_name);

	/*! @brief デストラクタ */
	~CGnuplot();

	/*! @brief 一時ファイル名 */
	static const std::string TempFileName;

	/*! @brief 正常に機能しているかどうか */
	bool Check();
	
	/*! @brief printfライクに指定のコマンドを実行 */
	void Command(const char* format, ...);

	/*! @brief 関数を描画 */
	void DrawFunc(const char* format);

	/* プロットタイプ */
	static const int PLOT_TYPE_NOOUTPUT = 0;	//< プロット時に一時ファイルを作成しない
	static const int PLOT_TYPE_OUTPUT = 1;		//< プロット時に一時ファイルを作成

	/*! @brief 1次元要素を描画 
	@param[in] cont プロット対称コンテナ
	@param[in] plot_type 直接gnuplotにデータを打ち込む(0: default)か，一時ファイルを作成するか(1: 未実装)の選択
	*/
	//template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	//void Plot(Container<T> cont, const int plot_type = PLOT_TYPE_OUTPUT, const char* file_name = TempFileName.c_str())
	template <class T>
	void Plot(std::vector<T> cont, const int plot_type = PLOT_TYPE_OUTPUT, const char* file_name = TempFileName.c_str())
	{
		//Container<T>::iterator it = cont.begin();
		typename std::vector<T>::iterator it = cont.begin();

		switch (plot_type) {
			case PLOT_TYPE_NOOUTPUT:
				Command("plot '-' w lp");
				while (it != cont.end()) {
					Command("%f", *it);
					it++;
				}
				Command("e");
				break;

			case PLOT_TYPE_OUTPUT:
				std::ofstream fout(file_name);
				while (it != cont.end()) {
					fout << *it << std::endl;
					it++;
				}
				Command("plot '%s' w lines", file_name);
				break;
		}
	}

	/*! @brief 1次元要素を描画（配列） */
	template <class T, int N>
	void Plot(T (&cont)[N], const int plot_type = PLOT_TYPE_OUTPUT, const char* file_name = TempFileName.c_str())
	{
		int x=0;

		switch (plot_type) {
			case PLOT_TYPE_NOOUTPUT:
				Command("plot '-' w lp");
				while (x < N) {
					Command("%f", cont[x]);
					x++;
				}
				Command("e");
				break;

			case PLOT_TYPE_OUTPUT:
				std::ofstream fout(file_name);
				while (x < N) {
					fout << cont[x] << std::endl;
					x++;
				}
				Command("plot '%s' w lines", file_name);
				break;
		}
	}

	/*! @brief 2次元要素を描画 */
	//template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	//void Plot(Container<T> contX, Container<T> contY, const int plot_type = PLOT_TYPE_OUTPUT, const char* file_name = TempFileName.c_str())
	template <class T>
	void Plot(std::vector<T> contX, std::vector<T> contY, const int plot_type = PLOT_TYPE_OUTPUT, const char* file_name = TempFileName.c_str())
	{
		//Container<T>::iterator itX = contX.begin();
		//Container<T>::iterator itY = contY.begin();
		typename std::vector<T>::iterator itX = contX.begin();
		typename std::vector<T>::iterator itY = contY.begin();
		switch (plot_type) {
			case PLOT_TYPE_NOOUTPUT:
				Command("plot '-' w lp");
				while (itX != contX.end() && itY != contY.end()) {
					Command("%f %f", *itX, *itY);
					itX++; itY++;
				}
				Command("e");
				break;

			case PLOT_TYPE_OUTPUT:
				std::ofstream fout(file_name);
				while (itX != contX.end() && itY != contY.end()) {
					fout << *itX << " " << *itY << std::endl;
					itX++; itY++;
				}
				Command("plot '%s' w lines", file_name);
				break;
		}
	}

	/*! @brief 2次元要素を描画（配列） */
	template <class T, int N, int M>
	void Plot(T (&contX)[N], T (&contY)[M], const int plot_type = PLOT_TYPE_NOOUTPUT, const char* file_name = TempFileName.c_str())
	{
		int x=0, y=0;
		switch (plot_type) {
			case PLOT_TYPE_NOOUTPUT:
				Command("plot '-' w lp");
				while (x < N && y < M) {
					Command("%f %f", contX[x], contY[y]);
					x++; y++;
				}
				Command("e");
				break;

			case PLOT_TYPE_OUTPUT:
				std::ofstream fout(file_name);
				while (x < N && y < M) {
					fout << contX[x] << " " << contY[y] << std::endl;
					x++; y++;
				}
				Command("plot '%s' w lines", file_name);
				break;
		}
	}

	/*! @brief Xラベルをセット */
	void SetXLabel(const char* format);

	/*! @brief Yラベルをセット */
	void SetYLabel(const char* format);

	/*! @brief Xプロット範囲を設定 */
	void SetXRange(const double x_min, const double x_max);

	/*! @brief Yプロット範囲を設定 */
	void SetYRange(const double y_min, const double y_max);

	/*! @brief リプロット */
	void Replot();
};


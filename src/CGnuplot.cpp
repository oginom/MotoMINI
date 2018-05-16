/*
 * http://tips.hecomi.com/entry/20100707/1278533304
 */

#include <stdio.h>
#include <stdarg.h>
#include "CGnuplot.h"

const std::string CGnuplot::TempFileName = "gnuplot_tmp.dat";

CGnuplot::CGnuplot()
{
  //Fp = _popen("pgnuplot", "w");
  Fp = popen("gnuplot -persist", "w");
  if (Fp == NULL) {
    printf("pipe error\n");
  }
}

CGnuplot::CGnuplot(const char* file_name)
{
  Fp = fopen(file_name, "w");
  if (Fp == NULL) {
    printf("pipe error\n");
  }
}

CGnuplot::~CGnuplot()
{
  pclose(Fp);
}

bool CGnuplot::Check()
{
  if (Fp == NULL) {
    return false;
  }
  return true;
}

void CGnuplot::Command(const char* format, ...)
{
  char buf[1024];
  va_list ap;

  va_start(ap, format);
  vsprintf(buf, format, ap);
  va_end(ap);

  fprintf(Fp, "%s\n", buf);
  Flush();
}

void CGnuplot::DrawFunc(const char* format)
{
  Command("plot %s", format);
}

void CGnuplot::SetXLabel(const char* format)
{
  Command("set xlabel '%s'", format);
}

void CGnuplot::SetYLabel(const char* format)
{
  Command("set ylabel '%s'", format);
}

void CGnuplot::SetXRange(const double x_min, const double x_max)
{
  Command("set xrange [%f:%f]", x_min, x_max);
}

void CGnuplot::SetYRange(const double y_min, const double y_max)
{
  Command("set yrange [%f:%f]", y_min, y_max);
}

void CGnuplot::Flush()
{
  fflush(Fp);
}

void CGnuplot::Replot()
{
  Command("replot");
}

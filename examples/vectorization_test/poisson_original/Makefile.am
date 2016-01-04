example_name  = poisson_original
check_SCRIPTS = run.sh
install_dir   = $(examples_install_path)/vectorization_test/poisson_original
data          = poisson_original.C exact_solution.C fe_shape_function.h run.sh
sources       = $(data) run.sh

CLEANFILES = out.pvtu

clean-local:
	-rm -rf out_*.vtu

##############################################
# include common example environment
include $(top_srcdir)/examples/Make.common

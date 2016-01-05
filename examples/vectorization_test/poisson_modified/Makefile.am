example_name  = poisson_modified
check_SCRIPTS = run.sh
install_dir   = $(examples_install_path)/vectorization_test/poisson_modified
data          = poisson_modified.C exact_solution.C fe_shape_function_1d.h fe_shape_function_simplified.h run.sh
sources       = $(data) run.sh

CLEANFILES = out.pvtu

clean-local:
	-rm -rf out_*.vtu

##############################################
# include common example environment
include $(top_srcdir)/examples/Make.common

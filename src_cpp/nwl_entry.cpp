#include <nwl_pch.hpp>
#include <nwl.hpp>
using namespace NW;

#define NWL_BUILD_EXE 1

#ifdef NWL_BUILD_EXE
int main(int nof_arguments, char* arguments[])
{
work_init:
	{
		mem_sys::on_init();
		cmp_sys::on_init();
		ent_sys::on_init();
		io_sys::on_init();
		data_sys::on_init();
	}
work_data_sys:
	{
		data_path dpath;
		for (auto& ipth_0 : dpath) {
			if (str_is_equal(str_part_right(ipth_0, '.'), ".git")) { continue; }
			io_sys::get_input() << dpath << " -> " << ipth_0 << std::endl;
			for (auto& ipth_1 : ipth_0) {
				io_sys::get_input() << '\t' << ipth_0 << " -> " << ipth_1 << std::endl;
				for (auto& ipth_2 : ipth_1) {
					io_sys::get_input() << "\t\t" << ipth_1 << " -> " << ipth_2 << std::endl;
					for (auto& ipth_3 : ipth_2) {
						io_sys::get_input() << "\t\t\t" << ipth_2 << " -> " << ipth_3 << std::endl;
					}
				}
			}
		}
		io_sys::update();
	}
	{
		switch (MessageBox(
			NULL,
			L"the program is finished;\nrepeat this again?",
			L"library_tests",
			MB_YESNO
		)) {
		case IDYES: { goto work_data_sys; }
		case IDNO: { goto work_quit; }
		}
	}
work_quit:
	{
		mem_sys::on_quit();
		cmp_sys::on_quit();
		ent_sys::on_quit();
		io_sys::on_quit();
		data_sys::on_quit();
	}
	return 0;
}
#endif
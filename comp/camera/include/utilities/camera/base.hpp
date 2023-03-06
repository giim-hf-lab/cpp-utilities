#ifndef __UTILITIES_CAMERA_BASE_HPP__
#define __UTILITIES_CAMERA_BASE_HPP__

#include <system_error>
#include <utility>

#include <opencv2/core.hpp>

namespace utilities::camera::base
{

struct reader
{
	inline virtual ~reader() noexcept = default;

	[[nodiscard]]
	virtual bool next_image(std::error_code& ec, cv::Mat& image) = 0;

	[[nodiscard]]
	inline virtual bool next_image(cv::Mat& image) final
	{
		std::error_code ec;
		auto ret = next_image(ec, image);
		if (ec)
			throw std::system_error(ec);
		return ret;
	}
};

struct device : public reader
{
	virtual void close() = 0;

	virtual void open() = 0;

	virtual void start(bool latest_only) = 0;

	virtual void stop() = 0;

	virtual void subscribe(bool exclusive) = 0;

	virtual void unsubscribe() = 0;
};

}

#endif

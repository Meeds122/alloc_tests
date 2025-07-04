https://x.com/Meeds1221/status/1940884751998706011

To calloc, or to malloc, which is faster? It seems that the consensus is that malloc is faster as calloc would zero the memory in the heap before returning the pointer resulting in additional computation cycles. Let's test it! 

You can see the code used and the data generated here:  https://github.com/Meeds122/alloc_tests

Each of the 500 data point represents a sample size of 200 allocation races per data point for an overall sample of 100,000 events. The testing was performed on a laptop running PopOS 22.04LTS. The code was compiled with GCC. 

Eventually, the data collected was imported into excel and converted into a graph. As we can see, calloc becomes much more time expensive just after the 15MB mark. 

What is more interesting to me is the 1 - 5,000,000 byte range. From the 1kb to 2mb range, representing around 150 datapoints, calloc ends up being a bit faster.  

I think I'll be using calloc for small memory allocations and malloc for large ones. 

Thanks!

//
// Created by steve on 4/7/17.
//
#include "../../Catch.hpp"
#include "../../src/MemAllocator.hpp"

void PlaceHolderFunction()
{
    printf("Not useful, ignore me totally");
}

TEST_CASE("Tests memory allocator for Unix platform","[MemAllocator],[MemAllocatorUnix]")
{
    std::cout << std::dec << "Process ID: " << getpid();
    PLH::MemAllocatorU allocator;
    PLH::ProtFlag R = PLH::ProtFlag::R;
    PLH::ProtFlag W = PLH::ProtFlag::W;
    PLH::ProtFlag X = PLH::ProtFlag::X;
    PLH::ProtFlag N = PLH::ProtFlag::NONE;

    REQUIRE(allocator.TranslateProtection(X) == PROT_EXEC);
    REQUIRE(allocator.TranslateProtection(W) == PROT_WRITE);
    REQUIRE(allocator.TranslateProtection(R) == PROT_READ);
    REQUIRE(allocator.TranslateProtection(N) == PROT_NONE);

    REQUIRE(allocator.TranslateProtection(X | W | R | N) == (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_NONE));

    uint64_t fnAddress = (uint64_t)&PlaceHolderFunction;
    std::cout << "fnAddress: " << std::hex << fnAddress << std::endl;

    int PageSize = getpagesize();
    std::cout << std::dec << "PageSize: " << PageSize << std::endl;
    for(PLH::MemoryBlock page : allocator.GetFreeVABlocks())
    {
        std::cout << std::hex << page.GetStart() << " " << page.GetEnd() << std::dec << " pages:" << page.CountPagesInBlock(PageSize) << std::endl;
    }
}



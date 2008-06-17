/**
 * @file Loader.h
 */

#ifndef __LOADER_H__
#define __LOADER_H__

#include "types.h"
#include "Thread.h"
#include "Scheduler.h"

struct sELF32_Phdr;
typedef struct sELF32_Phdr ELF32_Phdr;

struct sELF32_Ehdr;
typedef struct sELF32_Ehdr ELF32_Ehdr;

/**
* @class Loader manages the Addressspace creation of a thread
*/
class Loader
{
  public:

    /**
     *Constructor
     * @param file_image_ all needed data from the executable
     * @param thread Thread to which the loader should belong
     * @return Loader instance
     */
    Loader(int32 fd, Thread *thread);

    ~Loader();

    /**
     *Creates a new PageDirectory and a new Page for the stack and initialises them
     */
    void initUserspaceAddressSpace();

    /**
     *Frees the page directory of the current Thread
     */
    void cleanupUserspaceAddressSpace();

    /**
     *Initialises the Addressspace of the User, creates the Thread's
     *InfosUserspaceThread and sets the PageDirectory
     *
     * @return 0
     */
    uint32 loadExecutableAndInitProcess();

    /**
     *loads one page slow by its virtual address: gets a free page, maps it,
     *zeros it out, copies the page, one byte at a time
     * @param virtual_address virtual address where to find the page to load
     */
    void loadOnePageSafeButSlow ( uint32 virtual_address );

    //uint8 *getFileImagePtr() {return file_image_;}

    uint32 page_dir_page_;
  private:

    //uint8 *file_image_;
    uint32 fd_;
    //File *file_;
    Thread *thread_;
    ELF32_Ehdr *hdr;
    ELF32_Phdr **phdrs;
};

#endif

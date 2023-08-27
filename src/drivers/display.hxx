#ifndef __DRIVER_DISPLAY_HXX__
#define __DRIVER_DISPLAY_HXX__

#include <cstdint>
#include <pinout.h>

#define DISPLAY_NUMBER_OF_SECTIONS 3U
#define DISPLAY_RAW_REFRESH_RATE 60U

/// Refresh rate must be DISPLAY_RAW_REFRESH_RATE for each section
#define DISPLAY_REFRESH_RATE                                                   \
  (DISPLAY_RAW_REFRESH_RATE * DISPLAY_NUMBER_OF_SECTIONS)

#define DISPLAY_MASK_SEGMENT_A 0b01000000u
#define DISPLAY_MASK_SEGMENT_B 0b00100000u
#define DISPLAY_MASK_SEGMENT_C 0b00010000u
#define DISPLAY_MASK_SEGMENT_D 0b00001000u
#define DISPLAY_MASK_SEGMENT_E 0b00000100u
#define DISPLAY_MASK_SEGMENT_F 0b00000010u
#define DISPLAY_MASK_SEGMENT_G 0b00000001u

namespace drivers {
class display {
public:
  /**
   * @brief Which segments need to be enabled or disabled in a bit mask
   * (MSB) b b b b b b b b (LSB)
   *  	 | | | | | | | |
   *  	 e A B C D E F G
   * @note e is an Error flag (Empty segment)
   */
  using segment_mask_t = uint8_t;
  using section_id_t = uint8_t;

  /**
   * @brief Parse an ASCII character into a segment mask
   *
   * @param symbol ASCII character to parse
   * @return segment_mask_t Segment mask of that character
   */
  static segment_mask_t interpret_symbol(char symbol);

private:
  /** Currently shown section */
  section_id_t current_section = 0U;

  /** Binary content of each section (Index must be substracted with 1) */
  segment_mask_t sections[DISPLAY_NUMBER_OF_SECTIONS] = {0U, 0U, 0U};

public:
  /**
   * @brief Construct a new display object
   *
   */
  display() = default;

  /**
   * @brief Initialize the display
   * @note Section is 0 (No selected section)
   */
  void init() const;

  /**
   * @brief Set the content of a section with the given segment mask
   * @note Changes will be shown on next update
   *
   * @param section Section to write contents to
   * @param value Segments masked
   * @return true No errors
   * @return false Invalid section ID
   */
  bool set(section_id_t section, segment_mask_t value);

  /**
   * @brief Set the content of all sections at once
   *
   * @param section_data Array with section data (Indexed from 0)
   */
  void set(segment_mask_t section_data[DISPLAY_NUMBER_OF_SECTIONS]);

  /**
   * @brief Display a string with size DISPLAY_NUMBER_OF_SECTIONS
   *
   * @param content string of size DISPLAY_NUMBER_OF_SECTIONS + null terminator
   * @param string content_size, using strlen()
   */
  void set(char content[DISPLAY_NUMBER_OF_SECTIONS + 1],
           std::size_t content_size);

  /**
   * @brief Push a value into the right-most section, when a new value
   * is pushed, the value is moved to the next section to the left.
   * @note Changes will be shown on next update
   *
   * @param value Value to be pushed
   */
  void push(segment_mask_t value);

  /**
   * @brief Clear the contents of the section memory
   * @note Changes will be shown on next update
   *
   * @param section Section to write contents to
   * @return true No errors
   * @return false Invalid section ID
   */
  bool unset(section_id_t section);

  /**
   * @brief Erase all data from segments
   * @note Changes will be shown on next update
   */
  void clear();

  /**
   * @brief Render the next section
   * Must be called within loop to show values
   */
  void update();

private:
  /**
   * @brief Interpret and write characters to display for
   * the given configuration
   */
  void render() const;

  /**
   * @brief Clear segment data without clearing current section
   */
  void empty();
};
} // namespace drivers

#endif
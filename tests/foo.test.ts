import { buildRangeValues } from 'src/utils'
import { describe, expect, test } from 'vitest'

describe('data formatting for noUiSlider', () => {
  test('should format data correctly', () => {
    let values = [0, 1, 2, 3, 4, 5]
    let expected = {
      '0%': 1,
      '25%': 2,
      '50%': 3,
      '75%': 4,
      min: 0,
      max: 5,
    }
    expect(buildRangeValues(values)).toEqual(expected)
  })
})

export function buildRangeValues (values: number[]): {
    min: number
    max: number
    [key: string]: number
} {
    let min = values.shift()!
    let max = values.pop()!
    let step = 100 / values.length

    let steps: { [key: string]: number } = {}
    values.forEach((value, index) => {
        steps[`${step * index}%`] = value
    })

    return { ...steps, min, max }
}

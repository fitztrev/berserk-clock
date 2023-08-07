<script setup lang="ts">
const initialMinutes = useState('initialMinutes', () => 10)
const incrementSeconds = useState('incrementSeconds', () => 0)

const timeOptions = [0, 1, 2, 3, 5, 8, 10, 15, 20, 30, 45, 60, 90, 120]

const sliderMinuteIndex = useState('sliderMinuteIndex', () =>
    timeOptions.indexOf(initialMinutes.value)
)

const sliderSecondsIndex = useState('sliderSecondsIndex', () =>
    timeOptions.indexOf(incrementSeconds.value)
)

watch(sliderMinuteIndex, (newValue) => {
    initialMinutes.value = timeOptions[newValue]
})

watch(sliderSecondsIndex, (newValue) => {
    incrementSeconds.value = timeOptions[newValue]
})
</script>

<template>
    <div class="text-center text-[14vw]">
        {{ initialMinutes }}+{{ incrementSeconds }}
    </div>

    <div class="mx-4">
        <div>
            <input
                class="w-full"
                type="range"
                v-model.number="sliderMinuteIndex"
                min="0"
                :max="timeOptions.length - 1"
                list="timeOptions"
            />
        </div>
        <div class="mt-10">
            <input
                class="w-full"
                type="range"
                v-model.number="sliderSecondsIndex"
                min="0"
                :max="timeOptions.length - 1"
                list="timeOptions"
            />
        </div>
    </div>

    <datalist id="timeOptions">
        <option v-for="step in timeOptions.length" :value="step"></option>
    </datalist>
</template>

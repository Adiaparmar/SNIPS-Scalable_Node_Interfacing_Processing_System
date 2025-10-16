import { ExampleModule } from '../../src/modules/example.module';

describe('End-to-End Test for Example Module', () => {
    let exampleModule: ExampleModule;

    beforeAll(() => {
        exampleModule = new ExampleModule();
    });

    it('should perform a successful operation', async () => {
        const result = await exampleModule.performOperation();
        expect(result).toBeTruthy();
    });

    it('should handle errors gracefully', async () => {
        try {
            await exampleModule.performOperationWithError();
        } catch (error) {
            expect(error).toBeDefined();
        }
    });
});